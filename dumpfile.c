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

#define DF_NONE    0
#define DF_TITLE   1 << 0
#define DF_HEADER  1 << 1
#define DF_FOOTER  1 << 2

void writefile(void)
{
	int i;
	FILE *fp = fopen("dumpfile.txt", "w");
	
	for (i = 1; i < 4; i++)
	{
		fprintf(fp, "line %d", i);
		
		if (i < 3)
			fprintf(fp, "\n");
	}
	
	fclose(fp);
}

void printchars(char c, int count)
{
	int i;

	for (i = 0; i < count; i++)
		fputc(c, stdout);
	
	fputc('\n', stdout);
}

int dumpfile(char *filename, int attr)
{
	FILE *fp;
	char buffer[1025];

	fp = fopen(filename, "r");

	if (fp == NULL)
		return 0;

	if (attr & DF_HEADER)
		printchars('-', 79);

	if (attr & DF_TITLE)
	{
		printf("FILE: %s\n", filename);
		printchars('-', 79);
	}

	while (fgets(buffer, 1025, fp) != NULL)
		printf("%s", buffer);

	putchar('\n');

	if (attr & DF_FOOTER)
		printchars('-', 79);

	fclose(fp);

	return 1;
}

int main(void)
{
	writefile();
	
	if (!dumpfile("dumpfile.txt", DF_HEADER | DF_TITLE | DF_FOOTER))
		printf("can't open file");

	return 0;
}

