#pragma once
#include"headers.h"

#ifndef MAX_STD
#define MAX_STD 100
#endif // !MAX_STD

 char _FILE_PATH[MAX_STD];
 char _PARAM[5];
 FILE* sourceFile;
 FILE* outputFile;

char* sourceFileBuffer;

enum fileType {_sourceFile,_outputFile};


/*
* @param file path
* @return file pointer
*/
FILE* getFile(char* file_path,_Bool sourceFileFlag,char mode[])
{
	if(sourceFileFlag)
	{
		FILE* fp = fopen(file_path, mode);
		if (fp == NULL)
		{
			printf("[Error] Fail to open file! No such file\n");
			return NULL;
		}
		else
		{
			printf("[Debug] Seccess to open file\n");
			return fp;
		}
	}
	else
	{
		FILE* fp = fopen(file_path,mode);
		if (fp == NULL)
		{
			printf("[Error] Fail to create new file\n");
			return NULL;
		}
		else
		{
			printf("[Debug] Seccess to create new file\n");
			return fp;
		}
	}
}

void closeFile(FILE* fp, char* filePath)
{
	if (fclose(fp) != 0)
		printf("[Error] Fail to close file. Path: %s\n", filePath);
	else
		printf("[Debug] File closed\n");
}


/*
* @param file source
* @return file size of byte
*/
long reader(int fileSelct)
{
	if (fileSelct == _sourceFile)
	{	
		sourceFile = getFile(_FILE_PATH,true,"r");
		fseek(sourceFile,0L,SEEK_END);
		long fileSize = ftell(sourceFile);
		printf("[Debug] file size %ld B\n",fileSize);
		fseek(sourceFile,0L,SEEK_SET);
		sourceFileBuffer = (char*)malloc(fileSize*sizeof(char)+20);
		char ch=getc(sourceFile);
		int index = 0;
		while (ch != EOF)
		{
			sourceFileBuffer[index] = ch;
			ch = getc(sourceFile);
			index++;
		}
		printf("[Debug] source file buffer size %d\n",strlen(sourceFileBuffer));
		closeFile(sourceFile, _FILE_PATH);
		return fileSize;
	}
}

void writerInit()
{
	char copyright[] = "C language Lexical Analyzer Version 1.0\nCopyright (c) 2023 Unity Dell \nAll rights reserved.\n\n";
	outputFile = getFile("./tokens.txt",false,"w+");
	fprintf(outputFile, copyright);
	fprintf(outputFile,"Token             Token type          Encoding\n");
	fprintf(outputFile,"----------------------------------------------\n");
}

void fileWriter(char token[],char type[], int IN_code)
{
	fprintf(outputFile,"%-15s\t%-15s\t%5d\n",token,type,IN_code);
}

void writerClose()
{
	closeFile(outputFile,"./tokens.txt");
}

void getFilePath(int argc, char const* argv[])
{
	char startLetter = argv[argc - 1][0];
	if (argc == 2 && startLetter != '-')
		strcpy(_FILE_PATH, argv[argc - 1]);
	else if (argc == 3)
		strcpy(_FILE_PATH, argv[argc - 1]);
	else
		printf("[Warning] No file directory.\n");
}


void getParam(int argc, char const* argv[])
{
	char startLetter = argv[1][0];
	if (argc == 2 && startLetter == '-')
		strcpy(_PARAM, argv[1]);
	else if (argc == 3)
		strcpy(_PARAM, argv[1]);
}