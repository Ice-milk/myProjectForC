#include <stdio.h>

int main(void)
{
  int a = 0x1234;
  char *p = (char *)&a;

  printf("0x%x\n", *p);
  if (*p == 0x12)
  {
    printf("是大端\n");
  }
  else
  {
    printf("是小端\n");
  }

  return 0;
}
