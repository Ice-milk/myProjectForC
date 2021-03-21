#include <stdio.h>

int main(void)
{
  int a[8] = {1,9,3,4,2,6,7,5};
  int max1 = a[0], max2, temp, i, j, k;
  
  for(i=1; i<8; i++)
  {
    if(a[i]>max1){
      max1 = a[i];
      k = i;
    }
  }
  temp = a[0];
  a[0] = max1;
  a[k] = temp;

  max2 = a[1];
  for(j=2; j<8; j++){
    if(a[j]>max2){
      max2 = a[j];
      k = j;
    }
  }
  temp = a[1];
  a[1] = max2;
  a[k] = temp;

  printf("%d,%d\n",max1,max2);
  for(k=0; k<8; k++){
    printf("%d",a[k]);
  }

  return 0;
}
