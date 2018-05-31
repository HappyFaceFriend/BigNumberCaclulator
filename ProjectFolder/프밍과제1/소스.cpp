#include <stdio.h>
#include <string.h>
int isNum(char c);
int isOp(char c);

int main()
{
	int index = 0, opIdx = 0, numIdx = 0;
	char op[50];
	float num[100] = { 0 };
	char exp[150] = "";
	int i, j, minusFlag = 0;
	float result = 0;

	printf("[Calculator Program]\ntype stop to quit\n\n");
	while (1)
	{
		LoopStart:
		index = 0;
		opIdx = 0;
		numIdx = 0;
		printf("Input>>");
		scanf("%s", exp);
		if (strcmp(exp, "stop") == 0)
			break;
		while (exp[index] != 0)
		{
			if (isNum(exp[index]))
			{
				while (isNum(exp[index]))
				{
					num[numIdx] *= 10;
					num[numIdx] += exp[index] - '0';
					index += 1;
				}
				if (minusFlag == 1)
				{
					num[numIdx] *= -1;
					minusFlag = 0;
				}
				numIdx++;
			}
			else if (isOp(exp[index]))
			{
				if (exp[index] != '-' && !isNum(exp[index - 1]))
				{
					printf("Error : Typed operator wrongly\n");
					goto LoopStart;
				}
				if (index == 0 || (exp[index] == '-' && !isNum(exp[index - 1])))
					minusFlag = 1;
				else
					op[opIdx++] = exp[index];
				index++;

			}
			else
			{
				printf("Error : Unknown Character\n");
				goto LoopStart;
			}
		}
		if (opIdx + 1 != numIdx)
		{
			printf("Error : Operants do not match Operators\n");
			goto LoopStart;
		}
		for (i = 0; i < opIdx; i++)
		{
			if (op[i] == '*')
			{
				num[i] = num[i] * num[i + 1];
				for (j = i + 1; j < numIdx; j++)
					num[j] = num[j + 1];
				numIdx -= 1;
				for (j = i; j < opIdx; j++)
					op[j] = op[j + 1];
				opIdx -= 1;
				i -= 1;
			}
			else if (op[i] == '/')
			{
				if (num[i + 1] == 0)
				{
					printf("Error : Can't divide by 0\n");
					goto LoopStart;
				}
				num[i] = num[i] / num[i + 1];
				for (j = i + 1; j < numIdx; j++)
					num[j] = num[j + 1];
				numIdx -= 1;
				for (j = i; j < opIdx; j++)
					op[j] = op[j + 1];
				opIdx -= 1;
				i -= 1;
			}
		}
		result = num[0];
		for (i = 0; i < opIdx; i++)
		{
			if (op[i] == '+')
				result += num[i + 1];
			else if (op[i] == '-')
				result -= num[i + 1];
		}
		if ((int)result != result)
			printf("%s = %f\n\n",exp, result);
		else
			printf("%s = %d\n\n",exp, (int)result);
	}
	printf("End Program.");
	return 0;
}

int isNum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isOp(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return 1;
	else
		return 0;
}