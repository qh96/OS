#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

char buf [1024];
#define DEFALUT_COUNT 10
#define DASH '-'

void tail (int fd, int x) {
  int n;  
  int total_lines; 
  int i;
  int fd2 = open ("newfile", O_CREATE | O_RDWR);     
  while((n = read(fd, buf, sizeof(buf))) > 0 ){
    write (fd2, buf, n);                               
    for(i = 0; i <= n ; i++){
      if(buf[i] == '\n') {                               
        total_lines++;
      }
    }
  }
  close (fd2);
  if (n < 0) exit();
  int cur_line = 0;
  fd2 = open ("newfile", 0);  
  int start = total_lines - x;                   
  while((n = read(fd2, buf, sizeof(buf))) > 0 ){
    for (i = 0; i < n; i++) {
      
        if (cur_line >= start || total_lines < x){          
          printf(1, "%c", buf[i]);
        }
      
      else {
	if (buf[i] != '\n'){
	  continue;
	}   
        cur_line++;
      }
    }
  }
  close (fd2);     
  unlink("newfile");           
}

int main(int argc, char *argv[]) {
  int fd = 0;	
  int i;
  int count = DEFALUT_COUNT;	     
  if (argc <= 1) {
    tail(0, DEFALUT_COUNT);	
    exit();
  }
  for (i = 1; i < argc; i++) {	
    if (*argv[i] == DASH) {      
      argv[i] = argv[i] + 1;
      count = atoi(argv[i]++);
      
    }	else if((fd = open(argv[i], 0)) < 0)
       {
        exit();
      }
	else{continue;}
    
  }		 
  tail(fd, count);
  close(fd);
  exit();    
}
