#include "user.h"
#include "types.h"
#include "stat.h"
#include "fcntl.h"

char buf [1024];
#define DEFALUT_COUNT 10

void tail (int fd, int x) {
  int n;  
  int total_lines; 
  int fd2 = open ("newfile", O_CREATE | O_RDWR);     
  while((n = read(fd, buf, sizeof(buf))) > 0 ){
    write (fd2, buf, n);                               
    for(int i = 0; i <= n ; i++){
      if(buf[i] == '\n') {                               
        total_lines++;
      }
    }
  }
  close (fd2);
  if (n < 0){
    exit();
  }
  int cur_line = 0;
  fd2 = open ("newfile", 0);  
  int start = total_lines - x;                     
  while((n = read(fd2, buf, sizeof(buf))) > 0 ){
    for (int i = 0; i < n; i++) {
      if (buf[i] != '\n'){
        if (cur_line >= start || total_lines < x){          
          printf(1, "%c", buf[i]);
        }else{
          continue;
        }
      }
      else {   
        printf(1, "%c", '\n');
        cur_line++;
      }
    }
  }
  close (fd2);
  unlink("newfile");                  
}

int main(int argc, char *argv[]) {
  int fd = 0;	
  int x = DEFALUT_COUNT;	
  char cur;     
  if (argc <= 1) {
    tail(0, DEFALUT_COUNT);	
    exit();
  }
  for (int i = 1; i < argc; i++) {
	  cur = *argv[i];	
    if (cur == '-') {      
      argv[i]++;
      x = atoi(argv[i]++);
    }	else {
      if ((fd = open(argv[i], 0)) < 0) {
        exit();
      }
    }
  }		 
  tail(fd, x);
  close(fd);
  exit();    
}
