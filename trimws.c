/*
MIT License

Copyright (c) 2022 fseek-youtube

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>

/* headers needed for trimwhitespace */
#include <ctype.h>
#include <string.h>

/* options for trim */
typedef enum { ALL, LEFT, RIGHT } trim_type;

char *trimwhitespace(char *str, trim_type tt)
{
	char *end;
	
	/* check for empty string */
	if (*str == '\0')
		return str;
		
	/* trim left side */
	if (tt == ALL || tt == LEFT)
	{
		while (isspace(*str))
			str++;
	}
	
	if (tt == LEFT)
		return str;

	/* trim right side */
	end = str + strlen(str) - 1;
	
	while (end > str && isspace(*end))
		end--;
		
	/* set null terminator one element past last char */
	end[1] = '\0';

	return str;
}

int main(void)
{
	char str[] = "  Hello, World  ";
	
	printf("before trim: [%s]\n", str);
	printf("trim left:   [%s]\n", trimwhitespace(str, LEFT));
	printf("trim right:  [%s]\n", trimwhitespace(str, RIGHT));
	printf("trim all:    [%s]\n", trimwhitespace(str, ALL));
	
	return 0;
}
