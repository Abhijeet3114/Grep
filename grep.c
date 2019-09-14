#include<stdio.h>
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h> 
#include<stdlib.h>
#include<unistd.h>
#include<errno.h> 
#include<string.h>
#include<ctype.h>
#include"grep.h"

//basic grep wihtout options
void basicgrep(int argc, char *argv[]){
	if(argc ==3){
		int rfd, j = 0, number;
		int count = 0 ;
		char ch, temp[100];
		rfd = open(argv[2],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
		while(read(rfd, &ch, sizeof(char))) {
			if(ch != '\n'){
				temp[j++] = ch;
			}
			else{	temp[j] = '\0';
				if(strstr(temp, argv[1])) {
				printf("%s\n",temp);
				}
				memset(temp, 0, sizeof(temp));
				j = 0; 			
			}
		}
		close(rfd);
		}
	}
}
//displays version of grep
void gversion(){
	printf("grep (GNU grep) 2.27\nCopyright (C) 2016 Free Software Foundation, Inc.\nLicense GPLv3+: 	GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Mike Haertel and others, see <http://git.sv.gnu.org/cgit/grep.git/tree/AUTHORS>.\n");
}
//invert output
void invert(int argc, char *argv[]){
	if(argc == 4){
		int rfd, j = 0, number;
		int invertcount = 0;
		char ch, temp[100];
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
		while(read(rfd, &ch, sizeof(char))) {
			if(ch != '\n') {
				temp[j++] = ch;
			}
			else {	temp[j] = '\0';
				if(strstr(temp, argv[2])==NULL) {
					printf("%s\n",temp);
				}					
				memset(temp, 0, sizeof(temp));
				j = 0; 			
			}
		}
		close(rfd);
		}
	}
}

//case insensitive search
void isearch(int argc, char *argv[]){
	if(argc == 4 ){
		char tempcopy[100][1000];
		int rfd, j = 0,i = 0,k =0, number;
		int count = 0;
		char ch, temp[100], temp1[100], str[100];;
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
			strcpy(str, argv[2]);
			while( str[i] != -1) {
				str[i] = tolower(str[i]);
				i++;
			}
				str[i] = ' ';
			//printf("str:%s\n",str);
			while(read(rfd, &ch, sizeof(char))) {
				if(ch != '\n') {
					temp[j++] = ch;
				}
				else {	
					//printf("%s\n",temp);
					for(j = 0; temp[j]; j++)
						temp1[j] = tolower(temp[j]);
					temp1[j] = '\0';
					if(strstr(temp1, str)) { 
						printf("%s\n",temp);
					}
					memset(temp, 0, sizeof(temp));
					memset(temp1, 0, sizeof(temp1));
					j = 0; 			
				}
			}
		close(rfd);
		}
	}
	
}
//display count of matching lines
void count(int argc, char *argv[]) {	
	if(argc == 4){
		int rfd, j = 0, number;
		int count = 0 ;
		char ch, temp[100];
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
		while(read(rfd, &ch, sizeof(char))) {
			if(ch != '\n'){
				temp[j++] = ch;
			}
			else{	temp[j] = '\0';
				if(strstr(temp, argv[2])) {
				count++;				
				}
				memset(temp, 0, sizeof(temp));
				j = 0; 			
			}
		}
		printf("%d\n",count);
		close(rfd);
		}
	}
}
//display matching lines with their line number
void linenumber(int argc, char *argv[]) {	
	if(argc == 4){
		int rfd, j = 0, i = 1, number;
 		char ch, temp[100];
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
			while(read(rfd, &ch, sizeof(char))) {
				if(ch != '\n'){
					temp[j++] = ch;
				}
				else{	temp[j] = '\0';
					if(strstr(temp, argv[2])) {
					printf("%d : %s\n",i ,temp);				
					}
					i++;
					memset(temp, 0, sizeof(temp));
					j = 0; 			
				}
			}
		}
		close(rfd);
		
	}
}
// display filename if match found -l
void filename(int argc, char *argv[]) {
	if(argc == 4){
		int rfd, j = 0, number;
 		char ch, temp[100];
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
			while(read(rfd, &ch, sizeof(char))) {
				if(ch != '\n'){
					temp[j++] = ch;
				}
				else {	temp[j] = '\0';
					if(strstr(temp, argv[2])) {
					printf("%s\n",argv[3]);
					break;
					}
					memset(temp, 0, sizeof(temp));
					j = 0; 			
				}
			}
		}
		close(rfd);
		
	}
}
//whole word -w
void whword(int argc, char *argv[]){
	if(argc == 4){
		int rfd, j = 0, i = 0, flag = 0;
		int invertcount = 0;
		char ch, temp[100], word[100], tempcopy[100], *token;
		char delim[] = " .,-";
		rfd = open(argv[3],O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
		
		while(read(rfd, &ch, sizeof(char))) {
			if(ch != '\n') {
				temp[j++] = ch;
			}
			else {	temp[j] = '\0';
				strcpy(tempcopy, temp);
				token = strtok(temp, delim);
					while(token) {
						//printf("token is : %s\n",token);
						if(strcmp(token, argv[2]) == 0)
							printf("%s\n", tempcopy);
						token = strtok(NULL, delim);
					}
				memset(temp, 0, sizeof(temp));
				token = 0;
				j = 0; 			
			}
		}
		close(rfd);
		}
	}
}
//filesearch option -f
void filesearch(int argc, char *argv[]) {
	if(argc == 4){
		int rfd1, i = 0, size = 100;
		int rfd2, j = 0, size1 = 100;
 		char ch, ch1, *temp, *temp1, *token, * token1, *end_token, *end_token1;
		temp = malloc(size);
		temp1 = malloc(size1);
		if(temp == NULL || temp1 == NULL) {
			printf("memory out of bound");
			exit(1);		
		}
		rfd1 = open(argv[2],O_RDONLY);
		rfd2 = open(argv[3],O_RDONLY);
		if(rfd1 == -1 || rfd2 == -1) {
			perror("can't open file");
			exit(errno);
		}
		else {
			while(read(rfd1, &ch, sizeof(char))) {
				if(i >= size-1) {
					size = size + 10;
					temp = realloc(temp, size);
					if(temp == NULL) {
						printf("memory out of bound");
						exit(1);		
					}
				}
				temp[i++] = ch;
			}
			while(read(rfd2, &ch1, sizeof(char))) {
				if(j >= size1-1) {
					size1 = size1 + 10;
					temp1 = realloc(temp1, size1);
					if(temp1 == NULL) {
						printf("memory out of bound");
						exit(1);		
					}
				}
				temp1[j++] = ch1;
			}
			temp[i] = '\0';
			temp1[j] = '\0';
			//printf("%s\nfile2\n%s", temp, temp1);
			token = strtok_r(temp, "\n", &end_token);
			while(token) {
				//printf("token : %s\n", token);
				token1 = strtok_r(temp1, "\n", &end_token1);
				while( token1){
					//printf("token1 : %s\n", token1);
					if(strstr(token1, token))
						printf("%s\n", token1);
					 token1 = strtok_r(NULL, "\n", &end_token1);
				}
				token = strtok_r(NULL, "\n", &end_token);
			}
		}
		close(rfd1);
		close(rfd2);
		
	}
}
//MAX COUNT
void maxtext(int argc, char *argv[]) {
	if(argc == 5) {
		int rfd, i = 0, count = 0, max;
		char temp[100], ch;
		max = atoi(argv[2]);
		rfd = open(argv[4], O_RDONLY);
		if(rfd == -1) {
			perror("can't open file");
			exit(0);
		}
		else {
			while(read(rfd, &ch, sizeof(char))) {
				if(ch != '\n') {
					temp[i++] = ch;
				}
				else {	
					temp[i] = '\0';
					if(strstr(temp, argv[3])) {
						printf("%s\n",temp);
						count++;
					}
					memset(temp, 0, sizeof(temp));
					i = 0;
				}
				if(count == max)
					break;
			}
		}
	}
	else {
		printf("Invalid Arguments\n");
	}
}
//Byte offset
void byteoffset(int argc, char *argv[]) {
	if(argc == 4) {
			int rfd, i = 0, count = 0, j=0, max;
			char temp[100], ch;
			rfd = open(argv[3], O_RDONLY);
			if(rfd == -1) {
				perror("can't open file");
				exit(0);
			}
			else {
				while(read(rfd, &ch, sizeof(char))) {
					if(ch != '\n') {
						temp[i++] = ch;
						j++;
					}
					else {	
						temp[i] = '\0';
						if(strstr(temp, argv[2])) {
							if(count == 0)
							printf("0:%s\n",temp);
							else
							printf("%d:%s\n",j, temp);
							count++;
						}
						memset(temp, 0, sizeof(temp));
						i = 0;
					}
				}
			}
		}
		else {
			printf("Invalid Arguments\n");
		}
}
