#include <stdio.h>

#include "utils.h"

//long min(long a, long b) {
//	return a < b ? a : b;
//}
//
//long max(long a, long b) {
//	return a > b ? a : b;
//}


static void traverseTreeImpl(void* node, void* parentIt, traverseTreeParams* params)
{
	char it[params->iterStateSize];
	void* child = params->takeFirstChild(node, &it, parentIt, params->state);

	if (params->onEnterNode != NULL)
	{
		params->onEnterNode(node, &it, params->state);
	}

	while (child != NULL)
	{
		traverseTreeImpl(child, &it, params);
		child = params->takeNextChild(node, &it, parentIt, params->state);
	} 

	if (params->onExitNode != NULL)
	{
		params->onExitNode(node, &it, params->state);
	}
}

void traverseTree(void* root, traverseTreeParams* params)
{
	traverseTreeImpl(root, params, NULL);
}

void writeXmlEscapedDataString(FILE* out, char* str, int length)
{
	int i = 0;
	char ch = str[i];
	if (ch != 0)
	{
		int j = i;
		bool found = false;
		do 
		{
			char* escaped;
			switch (ch)
			{
			case '\n': escaped = "&#10;"; break;
			case '\r': escaped = "&#13;"; break;
			case '"': escaped = "&quot;"; break;
			case '&': escaped = "&amp;"; break;
			case '<': escaped = "&lt;"; break;
			case '>': escaped = "&gt;"; break;
			default: escaped = NULL; break;
			}
			if (escaped != NULL)
			{
				found = true;
				fwrite(&str[j], i - j, 1, out);
				fputs(escaped, out);
				fflush(out);
				j = i + 1;
			}
			i++;
			ch = str[i];
		} while (ch != 0 && i < length);

		if (found) 
		{
			if (j + 1 < i)
			{
				j++;
				fwrite(&str[j], i - j, 1, out);
			}
		}
		else 
		{
			fwrite(str, i, 1, out);
		}
	}
}

int alignSize(int size, int alignment)
{
	return size == 0 ? 0 : (size + (alignment - ((size - 1) % alignment)) - 1);
}

