#pragma once

#include"headers.h"

extern int keywords_count;
extern char* sourceFileBuffer;

bool isDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool isLetter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}

int isKeyword(char str[])
{
	if (strcmp(str, "\0") == 0)
		return -1;
	for (int i = 0; i < keywords_count; ++i)
	{
		if (strcmp(str, keywords[i]) == 0)
			return i;
	}
	return -1;
}

bool isBlank(char ch)
{
	if (ch == ' ')
		return true;
	else
		return false;
}

bool isNULL(char ch)
{
	if (ch == '\0')
		return true;
	else
		return false;
}

bool isBreak(char ch)
{
	if (ch == '\n')
		return true;
	else
		return false;
}

bool isTab(char ch)
{
	if (ch == '\t')
		return true;
	else
		return false;
}

void removeComment(char* sourceFileBuffer, long sourceFileSize)
{
	int lineCount = 0;
	int commentStart, commentEnd;
	commentStart = commentEnd = -1;
	for (long i = 0; i < sourceFileSize - 1; ++i)
	{
		if (sourceFileBuffer[i] == '\n'||sourceFileBuffer[i]=='\0')
			lineCount++;
		if (sourceFileBuffer[i] == '/')
		{
			if (sourceFileBuffer[i + 1] == '/')
			{
				commentStart = i;
				long temp = i;
				while (sourceFileBuffer[temp] != '\n')
					temp++;
				commentEnd = temp - 1;
			}
			else if (sourceFileBuffer[i + 1] == '*')
			{
				commentStart = i;

				if (commentStart + 2 < sourceFileSize)
				{
					char commentEndFlag = 0;
					for (long index = commentStart + 2; index < sourceFileSize; index++)
					{
						if (sourceFileBuffer[index] == '*' && sourceFileBuffer[index + 1] == '/')
						{
							commentEnd = index + 1;
							commentEndFlag = 1;
						}
					}
					if (!commentEndFlag)
					{
						printf("[Debug] invalid comment in line %d\n", lineCount+1);
						return;
					}
				}
			}
		}

		if (commentStart <= i && i <= commentEnd)
			sourceFileBuffer[i] = ' ';
	}
}