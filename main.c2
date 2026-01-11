#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main()
{
	for(int i=0; i < 6; i++)
	{
		char *str = get_next_line(0);
		if(str)
			printf("%s", str);
		else
			printf("%p", str);
		free(str);
	}
	return (0);
}