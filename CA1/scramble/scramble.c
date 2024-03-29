#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eoin.h"

int main(int argc, char *argv[])
{
	FILE *raw_file,*enc_file;
	char filename[51];
	char *file_in_ram;
	int filesize;	//the size of the file

	//set file to scrambele to first argument
	if(argv[1] != NULL)
	strcpy(filename,argv[1]);

	//ask user to enter filename if none provided
	else
	{
		printf("Enter name of file to encrypt\n");
		scanf("%50s",filename);
	}

	//open file
	raw_file=fopen(filename,"r");
	if(raw_file==NULL)
	{
		printf("Error opening input file\n");
		return 1;
	}

	//open output file
	strcat(filename,".sbl");
	enc_file=fopen(filename,"w+");
	if(enc_file==NULL)
	{
		printf("Error opening output file\n");
		return 2;
	}

	//find filesize
	fseek(raw_file, 0, SEEK_END);
	filesize=ftell(raw_file);
	rewind(raw_file);

	//load file into ram
	file_in_ram=malloc(filesize);
	fread(file_in_ram,1,filesize,raw_file);

	//perform encryption algorithm on file
	scramble(file_in_ram,filesize);

	//save encrypted file to disk
	fwrite(file_in_ram,1,filesize,enc_file);

	//free ram taken by file and close files
	fclose(raw_file);
	fclose(enc_file);
	free(file_in_ram);
}
