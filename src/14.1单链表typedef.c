/**
 * @file 13.1单链表typedef.c
 * @author Nie Yan
 * @brief 
 * 与13单链表相比，使用typedef代替了struct，使代码更清晰简洁
 * @version 0.1
 * @date 2021-03-28(creat)
 * @date 2021-03-28(last-change)
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
typedef struct LINK
{
  // 序号
  int id;
  // 数据
  int num;
  // 指向下一个链表元素
  struct LINK *next;
} Link, *PLink, **PPLink;

void input_data(PLink);
void add_element_h(PPLink);
void add_element_t(PPLink);
PLink search_item(int, PLink);
void insert_element(int, PPLink);
void change_item(int, PLink);
void delete_element(int, PPLink);
void print_element(PLink);
void print_all(PLink);
void release(PPLink);

/**
 * @brief 输入数据项
 * 
 * @param new_num 新的链表元素
 */
void input_data(PLink new_num)
{
  static int id = 1;
  if (new_num->id == 0)
  {
    new_num->id = id;
    id++;
  }
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
void add_element_h(PPLink head)
{
  /**
   * @param new_num 新建链表元素和缓存
   * @param temp 链表指针缓存
   */
  PLink new_num = NULL, temp = NULL;

  // 新建的数据不能放在栈空间，要存放在堆空间，否则函数结束值就丢失了
  new_num = (PLink)calloc(1, sizeof(Link)); // 使用calloc分配内存并初始化为0
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
    new_num->next = *head;
    *head = new_num;
  }
}

/**
 * @brief 尾插法添加元素
 * 
 * @param head 链表头指针的地址
 */
void add_element_t(PPLink head)
{
  PLink new_num = NULL;
  static PLink tail = NULL; // 用静态变量记录链表尾部
  if (*head != NULL)
  {
    PLink temp = *head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    tail = temp;
  }

  new_num = (PLink)calloc(1, sizeof(Link));
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
  }
  else
  {
    tail->next = new_num;
  }
  new_num->next = NULL;
  tail = new_num; // 尾指针始终指向链表尾部
};

/**
 * @brief 输入数据，查询含有相同数据项的所有数据元素并返回其指针
 * @param key 查询的数据
 * @param head 链表头指针
 * @return struct Link* 返回查询到的链表元素指针
 */
PLink search_item(int key, PLink head)
{
  PLink temp = head;
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
void insert_element(int id, PPLink head)
{
  PLink prev = NULL;
  PLink curr = *head;
  PLink new = NULL;

  while (NULL != curr && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  }

  new = (PLink)calloc(1, sizeof(Link));
  if (NULL == new)
  {
    printf("内存分配失败，按任意键结束...");
    getchar();
    exit(-1);
  }
  input_data(new);

  if (curr == NULL)
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
void change_item(int id, PLink head)
{
  PLink temp = head;
  while (temp != NULL && temp->id != id)
  {
    temp = temp->next;
  }
  if (temp == NULL)
  {
    printf("没有找到对应的元素\n");
    return;
  }
  printf("原元素的值为：\n");
  print_element(temp);
  printf("请输入新的值：\n");
  input_data(temp);
  printf("修改完毕，元素已改为：");
  print_element(temp);
}

/**
 * @brief 删除id对应的元素
 * 
 * @param id 元素id
 * @param head 链表首地址
 */
void delete_element(int id, PPLink head)
{
  PLink prev = NULL;
  PLink curr = *head;

  while (curr != NULL && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL)
  {
    printf("没有找到id对应的数据\n");
    return;
  }

  if (prev == NULL)
  {
    *head = curr->next;
  }
  else
  {
    prev->next = curr->next;
  }
  free(curr);
  printf("删除成功\n");
}

/**
 * @brief 打印单个元素内容
 * 
 * @param element 链表某个元素的指针
 */
void print_element(PLink element)
{
  if (NULL == element)
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
void print_all(PLink head)
{
  PLink temp = head;
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
void release(PPLink head)
{
  PLink temp = NULL;
  while (*head != NULL)
  {
    temp = (*head)->next; // ->优先级比*高，所以要括起来
    free(*head);
    *head = temp; // 对地址赋值，操作main函数中地址本身
  }
}

int main(void)
{
  PLink head = NULL; // @brief 链表头指针
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
    // 退出程序
    case 0:
      // 因为释放内存需要操作nums地址本身，所以还是要传入nums指针的地址
      release(&head);
      return 0;
      // 头插法
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

      // 尾插法
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

      // 插入数据
    case 3:
      while (1)
      {
        int id;
        printf("在id位置前插入数据，请输入id：");
        scanf("%d", &id);
        getchar();
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

      // 更改元素
    case 4:
      while (1)
      {
        int id;
        printf("请输入要更改的元素id：");
        scanf("%d", &id);
        getchar();
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

      // 删除元素
    case 5:
      while (1)
      {
        int id;
        printf("请输入要删除的元素id：");
        scanf("%d", &id);
        getchar();
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

      // 查询元素
    case 6:
      while (1)
      {
        int key; // 查询的值
        PLink search = head;
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

      // 打印整个链表
    case 7:
      printf("打印链表：\n");
      print_all(head);
      printf("按Enter继续...");
      getchar();
      break;

    default:
      continue;
    }
  }

  return 0;
}
