#include "types.h"
#include "stat.h"
#include "user.h"

#define BUF_MAX 512
#define NULL 0
//
char buf[BUF_MAX];



char* memchr(char *s, char c, int n){

	char *p =  s;
	while (n--){

		if (*p != c){


			p++;
		
		}
		else{

			return p;

		}

	}
	return NULL;


}

int stringCmp(const char * s1, const char * s2, int _i){

	char x,y;
	do{

		x = *s1++;
		y = *s2++;

		if (_i){

			x = (x>=65&&x<=90) ? x+32 : x;
			y = (y>=65&&y<=90) ? y+32 : y;


		}

	
		if (x=='\0'){break;}
	}while (x==y);
	return x-y;



}



//
void uniq(int fd, int _c, int _d, int _i){

	
	int line_count = 0;

	char *str = NULL;

	char *oldStr = NULL;
	int strLen=0;
	int cutLen = 0;
	int n;
	char *start, *cut;


	while ((n = read(fd, buf, sizeof(buf))) > 0){

		start = buf;

		while((cut = memchr(start, '\n', n)) != NULL){
			cut+=1;
			
			if (str != NULL && str[strLen-1] != '\n'){
				cutLen = cut-start;
				
				char *tmp = str;
				str = (char*)malloc(sizeof(char)*(cutLen+1+strLen));
				memset(str, '\0', cutLen+strLen+1);
				memmove(str, tmp, strLen);
				memmove(str+strLen, start, cutLen);
				
				//strConcat( cutLen,strLen, tmp, str,start);
				strLen += cutLen;
				start = cut;
				
			}
			else{
			
				cutLen = cut - start;
				str=(char*)malloc(sizeof(char)*(cutLen+1));
				memset(str, '\0', cutLen+1);
				memmove(str, start, cutLen);
				strLen = cutLen;
				start = cut;

			}
			

//
			if (str[strLen-1]=='\n'){
			
				
				if (oldStr==NULL){


					oldStr = str;
					line_count = 1;

				}
				else if (stringCmp(str, oldStr, _i)!=0){
					if (_c){printf(1, "%d ",line_count);}
					if (_d ){if (line_count>1) printf(1, "%s", oldStr);}
					else {printf(1, "%s", oldStr);}					
					oldStr = str;
					
					line_count=1;
				}
				else{

					line_count+=1;

				}
				strLen = 0;
				str = NULL;

			}

		}
		
		char *tmp = str;
		int cutLen = BUF_MAX - (start - buf);
		str = (char*)malloc(sizeof(char)*(cutLen+strLen+1));
		memset(str, '\0', cutLen+strLen+1);
		memmove(str, tmp, strLen);
		memmove(str+strLen, start, cutLen);
		strLen += cutLen;
		//strConcat( cutLen,strLen, tmp, str, start);
	}	

	if (_c){printf(1, "%d ",line_count);}
	if (_d ){if (line_count>1) printf(1, "%s", oldStr);}
	else {printf(1, "%s", oldStr);}


}




int 
main(int argc, char *argv[])
{


	int fd;


	if (argc <= 1){

	  uniq(0,0,0,0);
	  exit();

	}
	
	int _c = 0;
	int _d = 0;
	int _i = 0;
	int i = 0;
	for (i = 1; i < argc; i++){

		if (!stringCmp(argv[i], "-c", _i)){_c=1;}
		if (!stringCmp(argv[i], "-d", _i)){_d=1;}
		if (!stringCmp(argv[i], "-i", _i)){_i=1;}
	}
	

	if (_c==_d && _c == 1){printf(1,"uniq: -c and -d cannot appear at the same time!"); exit();}

	if ((fd = open(argv[argc-1],0)) < 0){

		printf(1, "uniq: cannot open %s\n", argv[argc-1]);
		exit();

	}
	
	uniq(fd,_c,_d,_i);
	close(fd);
	exit();

}





