void basicgrep(int argc, char *argv[]);		// normal grep command
void gversion();				//version 				-V
void invert(int argc, char *argv[]);		// print non matching lines		-v
void isearch(int argc, char *argv[]);		// case insensitivity -i 		-i
void count(int argc, char *argv[]);		//count 				-c	
void linenumber(int argc, char *argv[]);	//line number 				-n
void filename(int argc, char *argv[]);		// option -l not done properly		-l*
void whword(int argc, char *argv[]);		// whole word search 			-w
void filesearch(int argc, char *argv[]);	//one file is compared with 		-f
void maxtext(int argc, char *argv[]);		//grep 					-m
void byteoffset(int argc, char *argv[]);	// grep -b byte offset			-b
