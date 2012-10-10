#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define VER_MAJOR 1
#define VER_MINOR 0

struct FileMem {
	size_t fsize;
	char   *data;
};

void PrintHelp(){
	printf("Binary Replacing Editor v%i.%i\n\n",VER_MAJOR,VER_MINOR);
	printf("Usage:\t binedit -file=<filename> -src=<src string> -dst=<dest string>\n\n");
}

char *getCLArg(char *name,int argc,char *argv[]){
	char *pC = NULL;
	int i;
	for (i=1;i<argc;i++){
		if (strstr(argv[i],name)){
			pC = &argv[i][strlen(name)];
			break;
		}
	}
	return pC;
}

struct FileMem *getFileMem(char *filename){
	struct stat file_stat;
	FILE *in;
	struct FileMem *Buf;

	if(stat(filename, &file_stat) != 0) {
		perror("Could not stat");
		exit(2);
	}

	if ((in = fopen(filename,"rb"))==0){
		perror("Could not open");
		exit(2);
    }

	Buf = (struct FileMem *)malloc(sizeof(struct FileMem));
	Buf->data = (char *)malloc(file_stat.st_size);
	if (fread(Buf->data,file_stat.st_size,1,in)!=1){
		perror("file read error");
		exit(2);
	}
	Buf->fsize = file_stat.st_size;
	fclose(in);
	
	return Buf;
}

void saveFileMem(char *filename,struct FileMem *Buf){
	FILE *out;
	if ((out = fopen(filename,"wb"))==0){
		perror("Could not open for write");
		exit(2);
    }
	fwrite(Buf->data,Buf->fsize,1,out);
	fclose(out);
}

int hasHit(char *Buf, char *tmpl, size_t len){
	size_t i;
	for(i=0;i<len-1;i++)
		if (Buf[i]!=tmpl[i+1]) return 0;
	return 1;
}

void freeFileMem(struct FileMem *Buf){
	free(Buf->data);
	free(Buf);
}


int main(int argc, char *argv[]){
	char *filename,*src,*dst;
	struct FileMem *Buf;
	size_t src_len,c;
	

	if (argc!=4) {
		PrintHelp();
		return 1;
	};

	filename = getCLArg("-file=",argc,argv);
	src = getCLArg("-src=",argc,argv);
	dst = getCLArg("-dst=",argc,argv);

	if (!filename || !src || !dst){
		PrintHelp();
		return 1;
	}

	src_len = strlen(src);
	if(src_len!=strlen(dst)){
		printf("Scr and Dst should be the same length!\n");
		exit(3);
	}

	Buf = getFileMem(filename);
	c = 0;
	while(c<Buf->fsize-src_len){
		if (Buf->data[c++]!=src[0])
			continue;
		if (hasHit(&Buf->data[c],src,src_len))
			memcpy(&Buf->data[c-1],dst,src_len);
	}

	saveFileMem(filename,Buf);

	freeFileMem(Buf);

	return 0;
}