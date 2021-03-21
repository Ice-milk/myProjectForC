#include <stdio.h>

int main(void)
{
  char str[128];
  char* p = str;
  int count = 0;
  char temp;

  printf("请输入一串字符：\n");
  for(int i = 0; (temp = getchar()) != '\n' && temp != '\r'; i++)
  {
    str[i] = temp;
  }
  while(*p++ != '\0')
  {
    count++;
  }
  printf("%d\n", count);
  return 0;
}
