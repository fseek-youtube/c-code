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
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 20+1

void write_test_file();

int main(int argc, char *argv[])
{
	FILE *fp;
	char buffer[BUF_LEN];

	write_test_file();

	fp = fopen("test.txt", "r");
	
	while (fgets(buffer, BUF_LEN, fp) != NULL)
	{
		/* if no newline exists there is overflow that need to be stripped */
		if (strchr(buffer, '\n') == NULL)
		{
			char discard;

			/* since we're reading from a file we also need to check if the
			   string contains an end of file marker and break if it does,
			   otherwise we go into an infinite loop */
			while ((discard = fgetc(fp)) != '\n' && discard != EOF);
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		printf("%s\n", buffer);
	}

	fclose(fp);

	return 0;
}

#if defined(_WIN32) || defined(__MSDOS__)
  #include <io.h>
#else
  #include <unistd.h>
#endif

void write_test_file()
{
	FILE *fp;

	if (access("test.txt", 0) == 0)
		return;

	fp = fopen("test.txt", "w");

	fprintf(fp, "this line is short\n");
	fprintf(fp, "this line is much longer than the first line\n");

	fclose(fp);
}