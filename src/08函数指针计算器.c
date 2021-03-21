#include <stdio.h>

// 方法：加
int add(int, int);
// 方法：减
int sub(int, int);
// 使用方法计算两个数的值，输入函数指针和两个数，输出计算结果。
int calc(int (*fp)(int,int), int, int);
// 根据输入的字符判断使用的方法，返回函数指针
int (*select(char))(int,int);

int add(int a, int b)
{
  return a+b;
}

int sub(int a, int b)
{
  return a-b;
}

int calc(int (*fp)(int, int), int a, int b)
{
  return (*fp)(a, b);
}

int (*select(char op))(int,int)
{
  switch(op)
  {
    case '+':
      return add;
    case '-':
      return sub;
    default:
      return NULL;
  }
}

int main(void)
{
  int num1, num2;
  char op;
  int (*fp)(int,int);

  printf("请输入一个算式，例如1+2:\n");
  scanf("%d%c%d", &num1, &op, &num2);

  fp = select(op);
  if (fp == NULL)
  {
    printf("erro:select()返回指针为空\n");
    return -1;
  }
  printf("%d %c %d = %d\n", num1, op , num2, (*fp)(num1, num2));

  return 0;
}
