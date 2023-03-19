#pragma once

enum NUM_ID_encoding
{
	_number_encode=_while+1,
	_identifier_encode=_not+1
};

enum wordType 
{ 
	_keywords,
	_number,
	_delimiter,
	_operator,
	_identifier
};

char type[][30] =
{
	"keywords",
	"number",
	"delimiter",
	"operator",
	"identifier"
};
