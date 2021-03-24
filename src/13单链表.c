/**
 * @file 13单链表.c
 * @author Nie Yan
 * @brief 
 * 用结构体实现一个单链表，存放一串数字，并实现增改删查操作。
 * 注意指针的使用，记住一点，在main函数中的变量，需要在子函数中操作并改变，子函数中一定要通过指针来操作。
 * 例如在子函数中释放main函数中nums结构的内存，就需要用main函数中nums指针的地址来操作。
 * @version 0.1
 * @date 2021-03-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 链表数据结构
 * 
 */
struct Link
{
  // 序号
  int id;
  // 数据
  int num;
  // 指向下一个链表元素
  struct Link *next;
};

void input_data(struct Link *);
void add_element_h(struct Link **);
void add_element_t(struct Link **);
struct Link *search_item(int, struct Link *);
void insert_element(int, struct Link **);
void change_item(int, struct Link *);
void delete_element(int, struct Link **);
void print_element(struct Link *);
void print_all(struct Link *);
void release(struct Link **);

/**
 * @brief 输入数据项
 * 
 * @param new_num 新的链表元素
 */
void input_data(struct Link *new_num)
{
  static int id = 1;
  if (new_num->id == 0)
  {
    new_num->id = id;
  }
  id++;
  printf("请输入要存放的数字：\n");
  printf("num = ");
  scanf("%d", &(new_num->num));
  //丢弃一个回车符
  getchar();
}

/**
 * @brief 头插法添加链表元素
 * 
 * @param head 链表头指针的地址
 */
void add_element_h(struct Link **head)
{
  /**
   * @param new_num 新建链表元素和缓存
   * @param temp 链表指针缓存
   */
  struct Link *new_num = NULL, *temp = NULL;

  // 新建的数据不能放在栈空间，要存放在堆空间，否则函数结束值就丢失了
  new_num = (struct Link *)calloc(1,sizeof(struct Link));
  if (NULL == new_num)
  {
    printf("内存分配失败，按任意键程序退出...");
    getchar();
    exit(-1);
  }

  //输入数据
  input_data(new_num);

  if (NULL == *head)
  {
    *head = new_num;
    new_num->next = NULL;
  }
  else
  {
    // temp = *head;
    // *head = new_num;
    // new_num->next = temp;
    new_num->next = *head;
    *head = new_num;
  }
}

/**
 * @brief 尾插法添加元素
 * 
 * @param head 链表头指针的地址
 */
void add_element_t(struct Link **head)
{
  struct Link *new_num = NULL;
  static struct Link *tail = NULL;
  new_num = (struct Link *)calloc(1,sizeof(struct Link));
  if (NULL == new_num)
  {
    printf("内存分配失败，按任意键退出...\n");
    getchar();
    exit(-1);
  }

  input_data(new_num);

  if (NULL == *head)
  {
    *head = new_num;
    new_num->next = NULL;
  }
  else
  {
    tail->next = new_num;
    new_num->next = NULL;
  }
  tail = new_num;
};

/**
 * @brief 输入数据，查询含有相同数据项的所有数据元素并返回其指针
 * @param key 查询的数据
 * @param head 链表头指针
 * @return struct Link* 返回查询到的链表元素指针
 */
struct Link *search_item(int key, struct Link *head)
{
  struct Link *temp = head;
  while (NULL != temp)
  {
    if (temp->id == key || temp->num == key)
    {
      return temp;
    }
    temp = temp->next;
  }

  printf("完毕\n");
  return NULL;
}

/**
 * @brief 在id号前插入元素
 * 
 * @param id 链表元素序号
 * @param head 链表头指针
 */
void insert_element(int id, struct Link **head)
{
  struct Link *prev = NULL;
  struct Link *curr = *head;
  struct Link *new;

  while(NULL != curr && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  } 
  
  new = (struct Link *)calloc(1, sizeof(struct Link));
  if(NULL ==new)
  {
    printf("内存分配失败，按任意键结束...");
    getchar();
    exit(-1);
  }
  input_data(new);

  if (curr ==NULL)
  {
    printf("没有对应id的元素，将在链表末尾插入新的值\n");
  }
  
  if (prev == NULL)
  {
    *head = new;
  }
  else
  {
    prev->next = new;
  }
  new->next = curr;

  printf("插入成功！新插入元素为：\nprev:");
  print_element(prev);
  printf("new :");
  print_element(new);
  printf("curr:");
  print_element(curr);
}

/**
 * @brief 改变某个元素的值
 * 
 * @param id 元素id
 * @param head 链表头指针
 */
void change_item(int id, struct Link *head)
{
  struct Link *temp = head;
  while(temp != NULL && temp->id != id)
  {
    temp = temp->next;
  }
  if(temp == NULL)
  {
    printf("没有找到对应的元素\n");
  }
  else
  {
    printf("原元素的值为：\n");
    print_element(temp);
    printf("请输入新的值：\n");
    input_data(temp);
  }
  printf("修改完毕，元素已改为：");
  print_element(temp);
}

/**
 * @brief 删除id对应的元素
 * 
 * @param id 元素id
 * @param head 链表首地址
 */
void delete_element(int id, struct Link **head)
{
  struct Link *prev = NULL;
  struct Link *curr = *head;

  while(curr != NULL && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  }

  if(prev == NULL && curr != NULL)
  {
    curr = curr->next;
    free(*head);
    *head =curr;
  }
  else if(curr == NULL)
  {
    printf("没有找到id对应的元素\n");
  }
  else
  {
    prev->next = curr->next;
    free(curr);
  }
  printf("删除成功\n");
}

/**
 * @brief 打印单个元素内容
 * 
 * @param element 链表某个元素的指针
 */
void print_element(struct Link *element)
{
  if(NULL == element)
  {
    printf("NULL\n");
  }
  else
  {
    printf("%p: {%d : %d} -> %p \n", element, element->id, element->num, element->next);
  }
}

/**
 * @brief 输出整个链表
 * 
 * @param head 链表头指针
 */
void print_all(struct Link *head)
{
  struct Link *temp = head;
  while (temp != NULL)
  {
    print_element(temp);
    temp = temp->next;
  }
}

/**
 * @brief 释放整个链表内存
 * 
 * @param head 链表头指针的地址
 */
void release(struct Link **head)
{
  struct Link *temp = NULL;
  while (*head != NULL)
  {
    temp = (*head)->next; // ->优先级比*高，所以要括起来
    free(*head);
    *head = temp; // 对地址赋值，操作main函数中地址本身
  }
}

int main(void)
{
  struct Link *head = NULL; // @brief 链表头指针
  // 链表头指针不使用全局变量是因为全局变量容易被修改，不安全。
  while (1)
  {
    int num;
    printf("请输入对应数字：\n\
            1、添加新元素（头插法）\n\
            2、添加新元素（尾插法）\n\
            3、插入元素\n\
            4、更改某个元素的数据项\n\
            5、删除某个元素\n\
            6、查询数据项\n\
            7、打印整个链表\n\
            0、退出程序\n");
    scanf("%d", &num);
    getchar(); // 丢弃换行符，以免影响后面输入

    switch (num)
    {
    case 0:
      return 0;
    case 1:
      while (1)
      {
        // 因为函数中要修改的是head指针本身的值，所以需要传head指针的地址
        add_element_h(&head);

        char c;
        printf("是否继续添加新的元素？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    case 2:
      while (1)
      {
        // 因为函数中要修改的是head指针本身的值，所以需要传head指针的地址
        add_element_t(&head);

        char c;
        printf("是否继续添加新的元素？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    case 3:
      while (1)
      {
        int id;
        printf("在id位置前插入数据，请输入id：");
        scanf("%d", &id);
        insert_element(id, &head);

        char c;
        printf("是否继续插入元素？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    case 4:
      while (1)
      {
        int id;
        printf("请输入要更改的元素id：");
        scanf("%d", &id);
        change_item(id, head);

        char c;
        printf("是否继续更改元素？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }

      break;

    case 5:
      while (1)
      {
        int id;
        printf("请输入要删除的元素id：");
        scanf("%d", &id);
        delete_element(id, &head);

        char c;
        printf("是否继续删除元素？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }

      break;

    case 6:
      while (1)
      {
        int key; // 查询的值
        struct Link *search = head;
        printf("输入查询的值：\n");
        scanf("%d", &key);
        getchar();
        if (NULL == (search = search_item(key, search)))
        {
          printf("没有对应的信息\n");
        }
        else
        {
          printf("查询到的信息为：\n");
          print_element(search);
          search = search->next;
          while (NULL != (search = search_item(key, search)))
          {
            print_element(search);
            search = search->next;
          }
        }

        char c;
        printf("是否继续查询？y or n\n");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    case 7:
      printf("打印链表：\n");
      print_all(head);
      printf("按Enter继续...");
      getchar();
      break;

    default:
      continue;
    }
    continue;
  }

  // 因为释放内存需要操作nums地址本身，所以还是要传入nums指针的地址
  release(&head);

  return 0;
}
