#pragma once

enum Delimiter_encoding
{
	_parenthesis_left=42,
	_parenthesis_right,
	_bracket_left,
	_bracket_right,
	_brace_left,
	_brace_right,
	_back_slash,
	_semicolon,
	_single_quotes,
	_double_quotes,
	_dot,
	_comma,
	_sharp
};

char delimiter[][4]=
{
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	"\\",//use to escape character
	";",
	"'",
	"\"",
	".",
	",",
	"#"
};


int delimiter_count = _sharp-_parenthesis_left+1;