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
#include <stdlib.h>
#include <errno.h>

char **loadfile(char *filename, int buf_len, int *count);
void free_strarray(char **array, int count);

int main(int argc, char *argv[])
{
	char **lines;
	int count;
	int i;

	if (argc != 2)
	{
		printf("usage: %s <filename>\n", argv[0]);
		return 1;
	}

	lines = loadfile(argv[1], 101, &count);

	if (lines == NULL)
	{
		printf("error: %s\n", strerror(count));
		return 1;
	}

	for (i = 0; i < count; i++)
		printf("%s\n", lines[i]);

	free_strarray(lines, count);

	return 0;
}

char **loadfile(char *filename, int buf_len, int *count)
{
	FILE *fp;
	char **array;
	char *string;
	char *buffer;
	int line_count = 0;
	int array_size = 100;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		*count = errno;
		return NULL;
	}

	buffer = malloc(buf_len * sizeof(char));

	if (buffer == NULL)
	{
		*count = errno;
		fclose(fp);
		return NULL;
	}

	array = malloc(array_size * sizeof(char*));

	if (array == NULL)
	{
		*count = errno;
		fclose(fp);
		free(buffer);
		return NULL;
	}

	while (fgets(buffer, buf_len, fp) != NULL)
	{
		if (line_count == array_size)
		{
			char **newptr;

			array_size += 100;

			newptr = realloc(array, array_size * sizeof(char*));

			if (newptr == NULL)
			{
				*count = errno;
				fclose(fp);
				free(buffer);
				free_strarray(array, line_count);
				return NULL;				
			}

			array = newptr;
		}

		/* discard overflow */
		if (strchr(buffer, '\n') == NULL)
		{
			char discard;

			while ((discard = fgetc(fp)) != '\n' && discard != EOF);
		}
		
		buffer[strcspn(buffer, "\n")] = '\0';

		string = malloc(strlen(buffer) + 1);
		strcpy(string, buffer);

		array[line_count] = string;

		line_count++;
	}

	fclose(fp);
	free(buffer);

	*count = line_count;

	return array;
}

void free_strarray(char **array, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(array[i]);

	free(array);
}
