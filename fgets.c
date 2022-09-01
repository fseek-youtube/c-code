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
#include <string.h>

#define BUF_LEN 10+1

/* clean up stdin overflow and strip newline */
char *fgets_clean(char *buffer, int buf_len)
{
	fgets(buffer, buf_len, stdin);

	/* if no newline exists there is overflow that need to be stripped */
	if (strchr(buffer, '\n') == NULL)
		while (fgetc(stdin) != '\n');

	/* if newline does exist replace it with null terminator */
	buffer[strcspn(buffer, "\n")] = '\0';
	
	return buffer;
}

int main(void)
{
	char buffer[BUF_LEN];

	printf("enter more than 10 chars of text\n> ");
	fgets_clean(buffer, BUF_LEN);
	printf("%s\n", buffer);

	printf("enter some text\n> ");
	fgets_clean(buffer, BUF_LEN);
	printf("%s\n", buffer);

	return 0;
}
