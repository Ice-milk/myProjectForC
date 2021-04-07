#include <stdio.h>

int main(void)
{
  int n;
  printf("请输入字符个数：\n");
  scanf("%d", &n);
  // 丢弃缓冲区
  while (getchar() != '\n')
    ;
  char a[n + 1];
  printf("请输入字符串：\n");

  for (int i = 0; i < n; i++)
  {
    a[i] = getchar();
  }
  a[n] = '\0';

  printf("你输入的字符串是：%s\n", a);
  return 0;
}
