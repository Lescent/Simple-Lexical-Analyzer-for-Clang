#pragma once
#include"headers.h"

void print_type_encoding()
{
	printf("\n\tToken          Token type    Internal encoding\n");
	printf("\t----------------------------------------------\n");
	int i = 0;
	for (; i < keywords_count; i++)
		printf("\t%-15s %-10s %10d\n", keywords[i], type[_keywords], i + 1);
	printf("\t%-15s %-10s %10d\n", "???", type[_number], i + 1);
	for (i = 0; i < delimiter_count; ++i)
		printf("\t%-15s %-10s %10d\n", delimiter[i], type[_delimiter], keywords_count + i + 2);
	for (i = 0; i < operator_count; ++i)
		printf("\t%-15s %-10s %10d\n", Operator[i], type[_operator], keywords_count + delimiter_count + i + 2);
	printf("\t%-15s %-10s %10d\n", "???", type[_identifier], keywords_count + delimiter_count + i + 2);
}


void saveResult(int IN_code,char token[])
{
	char type[12];
	if (IN_code >= _auto && IN_code <= _while)
		strcpy(type, "Keywords");
	else if (IN_code == _number_encode)
		strcpy(type, "Number");
	else if (IN_code >= _parenthesis_left && IN_code <= _sharp)
		strcpy(type, "Delimiter");
	else if (IN_code >= _plus && IN_code <= _not)
		strcpy(type, "Operator");
	else if (IN_code == _identifier_encode)
		strcpy(type,"Identifier");
	fileWriter(token,type,IN_code);
}
