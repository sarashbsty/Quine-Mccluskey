/*
Copyright (c) 2025 Sarash Basumatary

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

#ifdef _WIN32
#include <windows.h>
#endif

#include "memory_tracker.h"
#include <stdio.h>
#include <stdlib.h>
#include "qm_run.h"
#include "display_qm.h"

static char* get_input();

int main()
{
	#ifdef _WIN32
	system("cls");
    SetConsoleOutputCP(CP_UTF8);
    #endif

	char *input = get_input();
	if(!input){
		puts("Failed to read input");
		return 1;
	}

	char *json_text = qm_run(input);
	puts(json_text);
	free(json_text);
//	display_qm(input);
	free(input);
	return 0;
}

static char* get_input(){
	size_t capacity = 200;
	size_t size = 0;
	char *buffer = malloc(capacity * sizeof(*buffer));
	if(buffer == NULL) return NULL;

	int ch;
	while((ch = getchar()) != '\n' && ch != EOF)
	{
		if (size >= capacity-1)
		{
			capacity = 2;
			char* temp = realloc(buffer , capacity * sizeof(*temp));
			if(!temp)
			{
				while ((ch = getchar()) != EOF);
				free(buffer);
				return NULL;
			}
			buffer = temp;
		}
		buffer[size++] = (char)ch;
	}

	buffer[size] = '\0';
	if(!size){ free(buffer); return NULL; }

	return buffer;
}

