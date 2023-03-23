#pragma once
#include"headers.h"

extern long sourceFileSize;
extern char* sourceFileBuffer;

long bufferAccessPointer = 0;

char strToken[MAX_STD];
int strTokenPointer = 0;

char getChar(char direciton)
{
	if (direciton == 'f')
	{
		if (bufferAccessPointer < sourceFileSize)
		{
			char ch = sourceFileBuffer[bufferAccessPointer];
			bufferAccessPointer++;
			return ch;
		}
	}
	else if (direciton == 'a')
	{
		if (bufferAccessPointer > 0)
		{
			bufferAccessPointer--;
			char ch = sourceFileBuffer[bufferAccessPointer];
			return ch;
		}
	}
}

void retrack()
{
	if (bufferAccessPointer > 0)
		bufferAccessPointer--;
}

void strTokenClear()
{
	strTokenPointer = 0;
	int flag = 0;
	for (int i = 0; i < MAX_STD; ++i)
	{
		flag = 0;
		if (strToken[i] != '\0')
		{
			strToken[i] = '\0';
			flag = 1;
		}
		if (flag == 0)
			break;
	}
}

//get valid token forward or afterward
void getValidToken(char* ch, char direction)
{
	if (direction == 'f')
	{
		while ((isBlank(*ch) || isNULL(*ch) || isBreak(*ch) || isTab(*ch)) && bufferAccessPointer < sourceFileSize)
		{
			*ch = getChar('f');
		}
	}
	else if (direction == 'a')
	{
		while ((isBlank(*ch) || isNULL(*ch) || isBreak(*ch) || isTab(*ch)) && bufferAccessPointer > 0)
		{
			*ch = getChar('a');
		}
	}

}


void Concat(char ch)
{
	if (ch != '\0')
	{
		strToken[strTokenPointer] = ch;
		strTokenPointer++;
	}
}

int analyzer()
{
	char ch = getChar('f');
	getValidToken(&ch, 'f');
	strTokenClear();
	//isNULL(ch) ? printf("[Debug] get char is NULL\n") : printf("[Debug] get char is %c\n", ch);
	//Keywords or identifier judge
	if (isLetter(ch))
	{
		while (isLetter(ch) || isDigit(ch) || ch == '_')
		{
			Concat(ch);
			ch = getChar('f');
		}
		retrack();
		int IN_code = isKeyword(strToken);
		if (IN_code != -1)
			return IN_code + 1;
		else
			return _identifier_encode;
	}
	//Keywords or identifier judge
	else if (ch == '_')
	{
		while (isLetter(ch) || isDigit(ch) || ch == '_')
		{
			Concat(ch);
			ch = getChar('f');
		}
		retrack();
		int IN_code = isKeyword(strToken);
		if (IN_code != -1)
			return IN_code + 1;
		else
			return _identifier_encode;
	}
	//Number judge
	else if (isDigit(ch))
	{
		if (ch == '0')
		{
			Concat(ch);
			ch = getChar('f');
			if (ch == 'x' || ch == 'X')
			{
				Concat(ch);
				ch = getChar('f');
				while (isDigit(ch)||(ch>='a'&&ch<='f')||(ch>='A'&&ch<='F'))
				{
					Concat(ch);
					ch = getChar('f');
				}
				retrack();
				return _number_encode;
			}
		}
		_Bool getDotFlag = false;
		_Bool getFloatFlag = false;
		while (isDigit(ch) || (ch == '.' && !getDotFlag&&!getFloatFlag)||((ch=='e'||ch=='E')&&!getFloatFlag))
		{
			if (ch == '.')
				getDotFlag = true;
			else if (ch == 'e' || ch == 'E')
				getFloatFlag = true;
			Concat(ch);
			ch = getChar('f');
		}
		retrack();
		return _number_encode;
	}
	//Number or dot judge
	else if (ch == '.')
	{
		Concat(ch);
		ch = getChar('f');
		if (isDigit(ch))
		{
			while (isDigit(ch))
			{
				Concat(ch);
				ch = getChar('f');
			}
			retrack();
			return _number_encode;
		}
		else
			retrack();
		return _dot;
	}
	//Delimiter judge
	switch (ch)
	{
	case '(':
	{
		Concat(ch);
		return _parenthesis_left;
	}
	case ')':
	{
		Concat(ch);
		return _parenthesis_right;
	}
	case '[':
	{
		Concat(ch);
		return _bracket_left;
	}
	case ']':
	{
		Concat(ch);
		return _bracket_right;
	}
	case '{':
	{
		Concat(ch);
		return _brace_left;
	}
	case '}':
	{
		Concat(ch);
		return _brace_right;
	}
	case '\\':
	{
		Concat(ch);
		return _back_slash;
	}
	case ';':
	{
		Concat(ch);
		return _semicolon;
	}
	case '\'':
	{
		Concat(ch);
		return _single_quotes;
	}
	case '\"':
	{
		Concat(ch);
		return _double_quotes;
	}
	case ',':
	{
		Concat(ch);
		return _comma;
	}
	case '#':
	{
		Concat(ch);
		return _sharp;
	}
	default:
		break;
	}

	if (ch == '<')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '<')
		{
			Concat(ch);
			ch = getChar('f');
			if (ch == '=')
			{
				Concat(ch);
				return _left_shift_equal;
			}
			else
			{
				retrack();
				return _left_shift;
			}
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _less_equal;
		}
		else
		{
			retrack();
			return _less;
		}
	}
	else if (ch == '>')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '>')
		{
			Concat(ch);
			ch = getChar('f');
			if (ch == '=')
			{
				Concat(ch);
				return _right_shift_equal;
			}
			else
			{
				retrack();
				return _right_shift;
			}
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _great_equal;
		}
		else
		{
			retrack();
			return _great;
		}
	}
	else if (ch == '+')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '+')
		{
			Concat(ch);
			return _increment;
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _plus_equal;
		}
		else
		{
			retrack();
			return _plus;
		}
	}
	else if (ch == '-')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '-')
		{
			Concat(ch);
			return _decrement;
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _sub_equal;
		}
		else if (isDigit(ch))
		{
			Concat(ch);
			_Bool getDotFlag=false;
			ch = getChar('f');
			while ((ch=='.'&&!getDotFlag)||isDigit(ch))
			{
				if (ch == '.')
					getDotFlag = true;
				Concat(ch);
				ch = getChar('f');
			}
			retrack();
			return _number_encode;
		}
		else
		{
			retrack();
			return _sub;
		}
	}
	else if (ch == '*')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _mul_equal;
		}
		else
		{
			retrack();
			return _mul_deref;
		}
	}
	else if (ch == '/')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _div_equal;
		}
		else
		{
			retrack();
			return _div;
		}
	}
	else if (ch == '%')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _mod_equal;
		}
		else
		{
			retrack();
			return _mod;
		}
	}
	else if (ch == '=')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _equal;
		}
		else
		{
			retrack();
			return _assignment;
		}
	}
	else if (ch == '?')
	{
		Concat(ch);
		return _question_mark;
	}
	else if (ch == ':')
	{
		Concat(ch);
		return _colon;
	}
	else if (ch == '&')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '&')
		{
			Concat(ch);
			return _and;
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _bit_and_equal;
		}
		else
		{
			retrack();
			return _bit_and_addr;
		}
	}
	else if (ch == '|')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '|')
		{
			Concat(ch);
			return _or;
		}
		else if (ch == '=')
		{
			Concat(ch);
			return _bit_or_equal;
		}
		else
		{
			retrack();
			return _bit_or;
		}
	}
	else if (ch == '^')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _bit_xor_equal;
		}
		else
		{
			retrack();
			return _bit_xor;
		}
	}
	else if (ch == '!')
	{
		Concat(ch);
		ch = getChar('f');
		if (ch == '=')
		{
			Concat(ch);
			return _not_equal;
		}
		else
		{
			retrack();
			return _not;
		}
	}
	else if (ch == '~')
	{
		Concat(ch);
		return _bit_not;
	}

	return -1;
}

