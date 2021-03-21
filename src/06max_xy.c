#include <stdio.h>

int max(int x, int y);

int main(void)
{
  int x,y;
  printf("请输入x y：\n");
  scanf(" %d %d", &x, &y);
  printf("max(x, y) = %d\n", max(x, y));
  return 0;
}

int max(int x, int y)
{
  if (x>y)
    return x;
  else
    return y;
}
