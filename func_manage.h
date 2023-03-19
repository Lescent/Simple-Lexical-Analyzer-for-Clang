#pragma once
#include"headers.h"
enum func { _print_typecode,_save_result,_func_count};

char funcEnable[2] = { 0 };

int funcSelect(char* argv_param, int len)
{
	int paramCount = 0;

	for (int i = 1; i < len; i++)
	{
		if (argv_param[i] == 'p')
		{
			funcEnable[_print_typecode]=1;
			continue;
		}
		else if (argv_param[i] == 's')
		{
			funcEnable[_save_result]=1;
			continue;
		}
	}
}

void printFuncRun()
{
	if (funcEnable[_print_typecode])
		print_type_encoding();
}

extern char strToken[MAX_STD];

void startAnalyze(long bufferAccessPointer, long sourceFileSize)
{
	if (funcEnable[_save_result])
	{
		writerInit();
		while (bufferAccessPointer < sourceFileSize)
		{
			int code=analyzer();
			if (code != -1)
			{
				printf("[Info] recognize token and its code: %10s %5d\n", strToken, code);
				saveResult(code,strToken);
			}
			else
				break;
		}
		printf("[Info] results have saved to file tokens.txt\n");
		writerClose();
	}
	else
	{
		while (bufferAccessPointer < sourceFileSize)
		{
			int code = analyzer();
			if (code != -1)
				printf("[Info] recognize token and its code: %10s %5d\n", strToken, code);
			else
				break;
		}
	}
}