#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 16384

void Help()
{
	printf("\nReplace a Line in a Text File...\nv1.0 Created by Kvc & anic17 - www.batch-man.com\n");
	printf("\nThere are 2 MODES to GET the results...");
	printf("\n MODE 1:\tGO INSIDE THE FILE, AND EDIT THAT LINE...");
	printf("\n MODE 2:\tREPLACE THAT LINE INSIDE THE FILE...\n");
	printf("\nSYNTAX:");
	printf("\nCall ReplaceLine [File] [LineNumber] [NewLineContent]\n");
	printf("\nReplaceLine will automatically, select the MODE whichever is faster for your");
	printf("\nGiven conditions\n");
	printf("\nINFO ABOUT THE MODES: [GET MAX OUT OF THIS UTILITIY]");
	printf("\nMODE 1 is much faster than MODE 2, as in MODE 2 - we create a new separate file");
	printf("\nand add the modified line to it at right place and then overwrite existing file");
	printf("\n(that is why, REPLACE LINE...)");
	printf("\n\nAND\n");
	printf("\nin MODE 1 - we are going to that line and changing its content and exiting, no");
	printf("\nrecreation of the entire file with 99%% unchanged rows");
	printf("\nBut, to invoke MODE 1 - it requires 1 special condition as FOLLOWS:");
	printf("\nCONDITION: Make Sure that the New line must have the same length as");
	printf("\nof previous line in the file, for compatibility...");
	printf("\nand you can check the Older line with \'ReadLine\' Utility & extract");
	printf("\nits length with \'getlen\'.");
	printf("\n\nFor Example: Replacing \"Kvc\" with \"abc\" will invoke Method 1.\n");
	printf("\nFor Example: Replacing \"Kvc\" with \"TheKvc\" will invoke Method 2.\n");
	printf("\n\t\"Notice, the number of characters in both cases.\"");
	printf("\n\nNOTE:");
	printf("\nThis utility will always choose the most efficient mode to complete the");
	printf("\nrequired action");
	return;
}

/*
	CHECKS THE LENGTH OF A STRING IN BINARY MODE...
	BETTER FUNCTION THAN STRLEN, AS IT OMITS THE AUTOMATIC CONVERSION AS PER THE OS
*/
int getLen(char array[])
{
	int i = 0;
	while (array[i] != '\0')
	{
		i++;
		if (array[i - 1] == '\r')
		{
			if (array[i] != 10)
			{
				printf("OLD MAC File detected...\n");
				printf("Please Convert it to Linux or Windows ASCII format file first!\n");
				exit(3);
			}
		}
	}
	return i;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Error: missing arguments\n");
		Help();
		return 1;
	}
	if (!strcmp(argv[1], "/?"))
	{
		Help();
		return 0;
	}
	/* File pointer to hold reference of input file */
	FILE *fTemp, *fOut;
	int i = 0, j = 0;
	char* file_open = argv[1];
	char buffer[BUFFER_SIZE];
	fTemp = fopen(argv[1], "rb+");
	//fOut = fopen(".temp", "wb+");

	/* fopen() return NULL if unable to open file in given mode. */
	if (fTemp == NULL)
	{
		fprintf(stderr, "%s: %s", file_open, strerror(errno));
		return errno;
	}

	int count = 0;

	while ((fgets(buffer, BUFFER_SIZE, fTemp)) != NULL)
	{
		count++;

		/* If current line is line to replace */
		if (count == atoi(argv[2]))
		{
			//checking length of both input and output string...
			int InputLen = getLen(argv[3]);
			int BuffLen = getLen(buffer);

			//looking for the terminating chars 'CRLF' / 'LF' / 'CR' in buffer...
			i = 2;
			while (i >= 0)
			{
				if ((int)buffer[BuffLen - i] == 13 || (int)buffer[BuffLen - i] == 10)
				{
					argv[3][InputLen] = buffer[BuffLen - i];
					//printf("----\n%d\t%d\n",buffer[BuffLen-i],argv[3][InputLen]);
					InputLen++;
				}
				else
				{
					argv[3][InputLen] = 0;
				}
				i--;
			}

			if (BuffLen == InputLen)
			{

				fseek(fTemp, -BuffLen, SEEK_CUR);
				fputs(argv[3], fTemp);
				fseek(fTemp, 0, SEEK_END);
				fclose(fTemp);
				return 1;
			}
			else
			{
				break;
			}
		}
	}

	//That means, we need to use the MODE 2
	fseek(fTemp, 0, SEEK_SET);
	fOut = fopen(".temp", "wb+");

	count = 0;
	while ((fgets(buffer, BUFFER_SIZE, fTemp)) != NULL)
	{
		count++;

		/* If current line is line to replace */
		if (count == atoi(argv[2]))
		{
			fputs(argv[3], fOut);
		}
		else
		{
			fputs(buffer, fOut);
		}
	}

	fclose(fTemp);
	fclose(fOut);

	remove(argv[1]);
	rename(".temp", argv[1]);

	return 2;
}
