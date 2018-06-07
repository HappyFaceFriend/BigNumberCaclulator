#include <stdio.h>
#include <string.h>

#define STRMAX 200

struct BigNum {
	char str[STRMAX];
	int sign;
};

int isNum(char c);
int isOp(char c);
int Num(char c);
char Char(int i);
void cutStr(char *dest, char *src, int count);
void strcpyBack(char *a, char *b);

void SetNum(char *str, struct BigNum *b);
void CopyNum(struct BigNum *dest, struct BigNum src);
void Print(struct BigNum a);
int NumComp(struct BigNum a, struct BigNum b);
struct BigNum Plus(struct BigNum a);
struct BigNum Minus(struct BigNum a);
struct BigNum Zero();
void trimZero(struct BigNum *a);

void Add(struct BigNum a, struct BigNum b, struct BigNum *result);
void Multiply(struct BigNum a, struct BigNum b, struct BigNum *result);
void Divide(struct BigNum a, struct BigNum b, struct BigNum *result);

int main()
{
	int index, opIdx, numIdx, i, j, k, minusFlag = 0;
	struct BigNum num[100],tempResult,result;
	char exp[150] = "", numStr[STRMAX] = "", op[50]="";

	printf("[Calculator Program]\ntype stop to quit\n\n");
	while (1)
	{
	LoopStart:
		index = 0;
		opIdx = 0;
		numIdx = 0;
		printf("\nInput>>");
		scanf("%s", exp);
		if (strcmp(exp, "stop") == 0)
			break;
		while (exp[index] != 0)
		{
			if (isNum(exp[index]))
			{
				k = 0;
				while (isNum(exp[index]))
					numStr[k++] = exp[index++];
				numStr[k] = '\0';
				SetNum(numStr, &num[numIdx]);
				if (minusFlag == 1)
				{
					num[numIdx].sign= -1;
					minusFlag = 0;
				}
				numIdx++;
			}
			else if (isOp(exp[index]))
			{
				if (exp[index] != '-' && (index == 0 || isOp(exp[index - 1])))
				{
					printf("Error : Typed operator wrongly\n");
					goto LoopStart;
				}
				if (minusFlag == 0 && exp[index] == '-' && (index == 0 || isOp(exp[index - 1])))
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
				Multiply(num[i], num[i + 1], &tempResult);
				CopyNum(&num[i], tempResult);
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
				if (num[i + 1].sign==0)
				{
					printf("Error : Can't divide by 0\n");
					goto LoopStart;
				}
				Divide(num[i], num[i + 1], &tempResult);
				CopyNum(&num[i], tempResult);
				for (j = i + 1; j < numIdx; j++)
					num[j] = num[j + 1];
				numIdx -= 1;
				for (j = i; j < opIdx; j++)
					op[j] = op[j + 1];
				opIdx -= 1;
				i -= 1;
			}
		}
		CopyNum(&result, num[0]);
		for (i = 0; i < opIdx; i++)
		{
			if (op[i] == '+')
				Add(result, num[i + 1], &result);
			else if (op[i] == '-')
			{
				num[i + 1].sign *= -1;
				Add(result, num[i + 1], &result);
			}
		}
		Print(result);
	}
	printf("End Program.");
	return 0;
}

//c�� ���ڸ� ��Ÿ���� 1, �ƴϸ� 0
int isNum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}
//c�� �����ڸ� 1, �ƴϸ� 0
int isOp(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return 1;
	else
		return 0;
}
//���ڸ� ���ڷ�
int Num(char c)
{
	return c - '0';
}
//���ڸ� ���ڷ�
char Char(int i)
{
	return i + '0';
}

//���ڿ��� count��ŭ�� �ڸ�
void cutStr(char *dest, char *src, int count)
{
	int i;
	for (i = 0; i < count; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}
//���ڿ� b�� a�� ����� ����
void strcpyBack(char *a, char *b)
{
	int len = strlen(b);
	char t[STRMAX];
	strcpy(t, b);
	int i;
	for (i = 0; i < len; i++)
		a[i] = t[len - i - 1];
	a[i] = '\0';
}


//BigNum�� str�� ��ȣ�ٿ� ���
void Print(struct BigNum a)
{
	if (a.sign > 0)
		printf("%s", a.str);
	else if (a.sign < 0)
		printf("-%s", a.str);
	else
		printf("0");
}
//���ڿ��� BigNum���� �ٲ� (��ȣ ��)
void SetNum(char *str, struct BigNum *b)
{
	int i;
	if (str[0] == '-')
	{
		for (i = 0; i < strlen(str); i++)
			str[i] = str[i + 1];
		b->sign = -1;
	}
	else if (strcmp(str, "0") == 0)
	{
		b->sign = 0;
		strcpy(b->str, str);
	}
	else
	{
		b->sign = 1;
		strcpy(b->str, str);
	}
}
//BigNum ����
void CopyNum(struct BigNum *dest, struct BigNum src)
{
	strcpy(dest->str, src.str);
	dest->sign = src.sign;
}
//BigNum�� ���� ��
int NumComp(struct BigNum a, struct BigNum b)
{
	int i;
	if (strlen(a.str) > strlen(b.str))
		return 1;
	else if (strlen(a.str) == strlen(b.str))
	{
		for (i = 0; i < strlen(a.str); i++)
		{
			if (a.str[i] > b.str[i])
				return 1;
			else if (a.str[i] < b.str[i])
				return -1;
		}
		return 0;
	}
	else
		return -1;
}
//����� �ٲ� ��ȯ
struct BigNum Plus(struct BigNum a)
{
	struct BigNum r;
	strcpy(r.str, a.str);
	r.sign = 1;
	return r;
}
//������ �ٲ� ��ȯ
struct BigNum Minus(struct BigNum a)
{
	struct BigNum r;
	strcpy(r.str, a.str);
	r.sign = -1;
	return r;
}
//0 ��ȯ
struct BigNum Zero()
{
	struct BigNum r;
	SetNum("0", &r);
	return r;
}
//���� ���� 0 ����
void trimZero(struct BigNum *a)
{
	int i, len = strlen(a->str);
	while (a->str[0] == '0' && a->str[1] != '\0')
	{
		for (i = 0; i < strlen(a->str) + 1; i++)
			a->str[i] = a->str[i + 1];
	}
}


//���� ��� result�� ����
void Add(struct BigNum a, struct BigNum b, struct BigNum *result)
{
	int lenA = strlen(a.str);
	int lenB = strlen(b.str);
	int t, i, carry;
	char nA[STRMAX], nB[STRMAX], nR[STRMAX] = "";
	if (a.sign == 0)
	{
		CopyNum(result, b);
		return;
	}
	else if (b.sign == 0)
	{
		CopyNum(result, a);
		return;
	}
	if (NumComp(a, b) >= 0)
	{
		strcpyBack(nA, a.str);
		strcpyBack(nB, b.str);
	}
	else
	{
		strcpyBack(nB, a.str);
		strcpyBack(nA, b.str);
		t = lenA;
		lenA = lenB;
		lenB = t;
	}
	carry = 0;
	if (a.sign == b.sign)   //+ +, - -
	{
		result->sign = a.sign;
		for (i = 0; i < lenA; i++)
		{
			t = Num(nA[i]) + carry;
			if (i < lenB)
				t += Num(nB[i]);
			nR[i] = Char(t % 10);
			carry = t / 10;
		}
		if (carry == 1)
		{
			nR[i] = Char(1);
			i++;
		}
	}
	else
	{
		if (NumComp(a, b) > 0)
			result->sign = a.sign;
		else if (NumComp(a, b) < 0)
			result->sign = b.sign;
		else
			result->sign = 0;
		for (i = 0; i < lenA; i++)
		{
			t = Num(nA[i]) - carry;
			carry = 0;
			if (i < lenB)
				t -= Num(nB[i]);
			if (t < 0)
			{
				carry = 1;
				nR[i] = Char(t + 10);
			}
			else
				nR[i] = Char(t);
		}
	}
	strcpyBack(result->str, nR);
	trimZero(result);

}
//���� ��� result�� ����
void Multiply(struct BigNum a, struct BigNum b, struct BigNum *result)
{
	struct BigNum temp;
	int lenA = strlen(a.str);
	int lenB = strlen(b.str);
	int t, i, j, carry;
	char nA[STRMAX], nB[STRMAX], nT[STRMAX] = "";
	if (a.sign == 0 || b.sign == 0)
	{
		SetNum("0", result);
		return;
	}
	if (NumComp(a, b) >= 0)
	{
		strcpyBack(nA, a.str);
		strcpyBack(nB, b.str);
	}
	else
	{
		strcpyBack(nB, a.str);
		strcpyBack(nA, b.str);
		t = lenA;
		lenA = lenB;
		lenB = t;
	}
	temp.sign = 1;
	SetNum("0", result);
	for (i = 0; i < lenB; i++)
	{
		carry = 0;
		for (j = 0; j < STRMAX; j++)
			nT[j] = 0;
		for (j = 0; j < lenA; j++)
		{
			t = Num(nA[j]) * Num(nB[i]) + carry;
			carry = t / 10;
			nT[j] = Char(t % 10);
		}
		if (carry > 0)
			nT[j] = Char(carry);
		strcpyBack(temp.str, nT);
		for (t = 0; t < i; t++)
			strcat(temp.str, "0");
		Add(Plus(temp), *result, result);
	}
	if (a.sign == b.sign)
		result->sign = 1;
	else
		result->sign = -1;

	trimZero(result);
	/*
	1. �μ����� �������� �ؿ� �ΰ� ū���� ���� ��
	2. ū�� * �������� ù�ڸ��� temp�� ����
	3. ū�� * �������� ���ڸ��� �ؼ� *10 �� ���ؼ� ����
	*/
}
//������ ��� result�� ����
void Divide(struct BigNum a, struct BigNum b, struct BigNum *result)
{
	struct BigNum temp, cloneA, cloneB, resultTemp, one;
	char sliceStr[STRMAX] = "", countStr[2] = "0";
	int lenA = strlen(a.str);
	int lenB = strlen(b.str);
	int count, shift = 0, i;
	SetNum("0", result);
	if (a.sign == 0)
		return;
	CopyNum(&cloneA, Plus(a));
	while (shift + lenB <= lenA)
	{
		CopyNum(&cloneB, Minus(b));
		strcpy(countStr, "0");
		strcat(result->str, "0");
		cutStr(sliceStr, cloneA.str, lenB + shift);
		SetNum(sliceStr, &temp);
		for (i = 0; i < lenA - lenB - shift; i++)
			strcat(cloneB.str, "0");
		count = 0;
		while (cloneA.sign >= 0)
		{
			count++;
			Add(cloneA, Minus(cloneB), &cloneA);
		}
		count--;
		Add(cloneA, Plus(cloneB), &cloneA);
		countStr[0] += count;
		SetNum(countStr, &temp);
		Add(*result, temp, result);
		shift++;
	}
	trimZero(result);
}