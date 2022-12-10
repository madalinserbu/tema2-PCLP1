#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tasks.h"
#include "strassen.h"

int main(void)
{
	char c;//character that reads the given command
	int ***arr;
	arr = NULL; //sau ***arr = NULL
	int curr = 0;
	indexes *sizes = NULL;

	sizes = (indexes *)malloc(sizeof(indexes));
	arr = (int ***)malloc(sizeof(int **));

	do {
		c = fgetc(stdin);
		if (c != ' ' && c != '\n') {
			switch (c) {
			case 'L':
				arr = load(&curr, arr, &sizes);
				break;
			case 'D':
				dimension(curr, sizes);
				break;
			case 'P':
				print(curr, arr, sizes);
				break;
			case 'C':
				crop(curr, arr, sizes);
				break;
			case 'M':
				arr = multiply_matrix(&curr, arr, &sizes);
				break;
			case 'F':
				arr = free_data(&curr, arr, &sizes);
				break;
			case 'O':
				sort(curr, arr, sizes);
				break;
			case 'T':
				transpose(curr, arr, sizes);
				break;
			case 'S':
				arr = task_strassen(&curr, arr, &sizes);
				break;
			case 'Q':
				quit(curr, arr, sizes);
				break;
			default:
				//warning message
				printf("Unrecognized command\n");
				break;
			}
		}
	} while (c != 'Q');
	return 0;
}
