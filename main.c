#include "monty.h"

/**
 * main - the main interpreted
 * @argc: number of args
 * @argv: args
 * Return: int
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char buffer[1024];
	unsigned int line_number = 0;
	char opcode[64];
	int argument;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	while (fgets(buffer, sizeof(buffer), file))
	{
		line_number++;
		if (sscanf(buffer, "%63s %d", opcode, &argument) == 2)
		{
			if (strcmp(opcode, "push") == 0)
				push_opcode(&stack, argument);

			else
			{
				fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
				fclose(file);
				return (EXIT_FAILURE);
			}
		}
		else if (strcmp(opcode, "pall") == 0)
			pall_opcode(&stack, line_number);
	}
	fclose(file);
	return (EXIT_SUCCESS);
}
