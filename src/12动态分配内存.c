/*
 * 根据输入的字符串，动态分配存储空间，然后输出，合理运用内存，
 * 但是因为使用getchar，输入内容退格修改可能出问题。
 * 2021.3.18
 * by: Nie Yan
 * */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main(void)
{
  char c;
  int count = 0;
  char *ptr = NULL; //必须初始化为空指针

  printf("请输入一段文字，回车结束：\n");
  while((c = getchar()) != '\n') 
  {
    count ++;
    char *new_ptr = (char *)realloc(ptr, (count + 1) * sizeof(char));
    if(new_ptr == NULL)
    {
      printf("分配内存不成功\n");
      free(ptr); // 释放原内存，并退出程序
      return -1;
    }
    else
    {
      ptr = new_ptr;
      ptr[count - 1] = c;
      ptr[count] = '\0';
    }
  }

  printf("你输入的文字为：%s\n", ptr);
  // printf("共占用内存：%d 字节\n", _msize(ptr)); // _msize()是windows独有函数
  free(ptr);

  return 0;
}
