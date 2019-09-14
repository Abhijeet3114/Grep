#include<string.h> 
#include<stdlib.h>
#include"grep.h"
int main(int argc, char *argv[]) {
	if(argc == 1) exit(0);
	if(strcmp(argv[1],"-V") == 0)
	gversion(argv);
	basicgrep(argc, argv);	
	if(strcmp(argv[1],"-v") == 0)
	invert(argc, argv);
	if(strcmp(argv[1],"-i") == 0)
	isearch(argc, argv);
	if(strcmp(argv[1], "-c") == 0)
	count(argc, argv);
	if(strcmp(argv[1], "-n") == 0)
	linenumber(argc, argv);
	if(strcmp(argv[1], "-l") == 0)
	filename(argc, argv);
	if(strcmp(argv[1], "-w") == 0)
	whword(argc, argv);
	if(strcmp(argv[1], "-f") == 0)
	filesearch(argc, argv);
	if(strcmp(argv[1], "-m") == 0)
	maxtext(argc, argv);
	if(strcmp(argv[1], "-b") == 0)
	byteoffset(argc, argv);
}

