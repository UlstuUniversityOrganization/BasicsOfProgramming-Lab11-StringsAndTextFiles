#include <stdio.h>
#include <string>

#define ARRAY_SIZE 1000
#define MAX_SYMBOLS 512

#define TRUE 1
#define FALSE 0

void SetNop(char*& string, const char* inputStr)
{
	int strLength = strlen(string);
	int inputStrLength = strlen(inputStr);

	for (int i = 0; i < strLength; i++)
	{
		if (string[i] == 'a' || string[i] == 'A')
		{
			memcpy(string + i + inputStrLength, string + i + 1, strLength - i);
			strLength += inputStrLength;
			for (int j = 0; j < inputStrLength; j++)
			{
				string[i] = inputStr[j];
				i++;
			}
		}
	}

}

void SetNopWorded(char*& string, const char* inputStr)
{
	int strLength = strlen(string);
	int inputStrLength = strlen(inputStr);
	size_t wordBeginning = -1;
	size_t wordEnd = -1;
	int aIs = 0;
	if (string[0] != ' ')
		wordBeginning = 0;
	for (int i = 0; i <= strLength; i++)
	{
		if (i != 0)
		{
			if (string[i - 1] == ' ')
				wordBeginning = i;
		}
		if (string[i] == 'a' || string[i] == 'A')
			aIs = TRUE;
		if (wordEnd >= 0)
		{
			if (i != strLength)
			{
				if ((string[i + 1] == ' ' || (wordBeginning >= 0 && wordEnd >= 0 && i + 1 >= strLength)) && aIs == TRUE)
				{
					memcpy(string + wordBeginning + inputStrLength, string + i + 1, strLength - i + 1);
					strLength += inputStrLength - (i - (wordBeginning - 1));
					i = wordBeginning;
					for (int j = 0; j < inputStrLength; j++)
					{
						string[i] = inputStr[j];
						i++;
					}
					aIs = FALSE;
				}
			}
		}
		if (i == strLength - 2)
			int point = inputStrLength - 2;
		if (string[i] == '\0')
		{

			for (int j = i + 1; j < MAX_SYMBOLS; j++)
				string[j] = ' ';
			break;
		}
	}
}

int main()
{
	FILE* filePointer;
	fopen_s(&filePointer, "data.txt", "rt");

	unsigned int stringsCount = ARRAY_SIZE;
	char** strings = new char* [stringsCount];
	for (int i = 0; i < stringsCount; i++)
		strings[i] = nullptr;

	int id = 0;
	while (!feof(filePointer))
	{
		strings[id] = new char[MAX_SYMBOLS];
		fgets(strings[id], MAX_SYMBOLS, filePointer);
		id++;
	}
	stringsCount = id;
	fclose(filePointer);
	fopen_s(&filePointer, "site.html", "wt");
	for (int i = 0; i < stringsCount; i++)
	{
		int len = strlen(strings[i]);
		if (i < stringsCount - 1)
			strings[i][len - 1] = '\0';
	}

	fputs("<HTML>\n", filePointer);
	fputs("    <HEAD>\n", filePointer);
	fprintf(filePointer, "    <TITLE>%s</TITLE>\n", strings[0]);

	for (int i = 0; i < stringsCount; i++)
		SetNopWorded(strings[i], "<i><b>NOP</b></i>");
	fputs("    </HEAD>\n", filePointer);
	fputs("    <BODY>\n", filePointer);
	for (int i = 0; i < stringsCount; i++)
	{
		if (strings[i])
		{
			if (i == 0)
			{
				int len = strlen(strings[i]);
				fprintf(filePointer, "        <H1> %s <BR></H1>\n", strings[i]);
				strings[i][len - 1] = '\n';
			}
			else
				fprintf(filePointer, "        %s <BR>\n", strings[i]);
		}
		else
			break;
	}
	fputs("    </BODY>", filePointer);
	fputs("\n", filePointer);
	fputs("</HTML>", filePointer);
}