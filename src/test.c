#include <stdio.h>
#include <stdlib.h>

struct Link 
{
  int num;
  struct Link *next;
};

void input(struct Link *);
void addNum(struct Link **);
void output(struct Link *);
void release(struct Link *);

void input(struct Link *new_num)
{
  printf("num = ");
  scanf("%d", &(new_num->num));
  getchar();
}

void addNum(struct Link **head)
{
  struct Link *new_num = NULL, *temp = NULL;
  new_num = (struct Link *)malloc(sizeof(struct Link));
  if(new_num == NULL)
  {
    printf("内存分配失败，按任意键退出...");
    getchar();
    exit(-1);
  }

  input(new_num);
  if(*head == NULL)
  {
    *head = new_num;
    new_num->next = NULL;
  }
  else
  {
    temp = *head;
    *head = new_num;
    new_num->next = temp;
  }
}

void output(struct Link *nums)
{
  int count = 0;
  struct Link *temp = nums;
  while(temp != NULL)
  {
    count++;
    printf("%d : %d\n", count, temp->num);
    temp = temp->next;
  }
}

void release(struct Link *nums)
{
  struct Link *temp = NULL;
  while(nums != NULL)
  {
    temp = nums->next;
    free(nums);
    nums = temp;
  }
}

int main(void)
{
  struct Link *nums = NULL;
  printf("%zd", sizeof(nums->next));
  while(1)
  {
    printf("添加数据？y or n\n");
    char c = getchar();
    getchar();
    if(c == 'y')
    {
      addNum(&nums);
    }
    else if(c == 'n')
    {
      break;
    }
    else
    {
      printf("请输入y或者n\n");
    }
  }

  while(1)
  {
    printf("打印链表中的所有值？y or n\n");
    char c = getchar();
    getchar();
    if(c == 'y')
    {
      output(nums);
    }
    else if(c == 'n')
    {
      break;
    }
    else
    {
      printf("请输入y或者n\n");
    }
  }

  release(nums);
  printf("%zd", sizeof(nums->next));

  return 0;
}
