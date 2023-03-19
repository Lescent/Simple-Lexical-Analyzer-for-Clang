#include"headers.h"

extern char* sourceFileBuffer;
extern long bufferAccessPointer;

extern FILE* sourceFile;
extern char _FILE_PATH[MAX_STD];
extern char _PARAM[5];
extern char strToken[MAX_STD];

long sourceFileSize;

int main(int argc, char const* argv[])
{
	if (argc < 2 || argc>3)
	{
		usage();
		exit(1);
	}
	
	getFilePath(argc, argv);
	getParam(argc, argv);

	if (_PARAM[0] != '\0')
	{
		int len = strlen(_PARAM);
		printf("[Debug] Parameter: %s\n", _PARAM);
		funcSelect(_PARAM,len);
	}

	if (_FILE_PATH[0] != '\0')
	{
		char fullPath[MAX_STD];
		if (_fullpath(fullPath, _FILE_PATH, MAX_STD) != NULL)
			printf("[Debug] File Path: %s\n", fullPath);
		else
			printf("[Debug] Fail to access full path\n");
		sourceFileSize = reader(_sourceFile);

		if (sourceFileSize == 0)
		{
			printf("[Warning] File is NULL. Lexer exit.\n");
			exit(-1);
		}
		else
		{
			removeComment(sourceFileBuffer,sourceFileSize);
			startAnalyze(bufferAccessPointer,sourceFileSize);
		}

	}

	printFuncRun();

	free(sourceFileBuffer);
	return 0;
}
