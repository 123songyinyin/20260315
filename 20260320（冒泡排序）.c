#include<stdio.h>

// 修改参数类型为 int arr[]（等价于 int *arr），增加标志位优化
void bubble_sort(int arr[], int sz)
{
    int i=0;
    for(i=0;i<sz-1;i++)
    {
        // 增加标志位，标记本轮是否有交换
        int flag = 1; // 初始假设已有序
        int j=0;
        for(j=0;j<sz-1-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                // 发生交换，说明数组还未排序完成
                flag = 0;
                int tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
            }
        }
        // 如果本轮没有交换，直接退出循环
        if(flag == 1)
        {
            break;
        }
    }
}

int main()
{
    int arr[]={9,8,7,6,5,4,3,2,1,0};
    int sz=sizeof(arr)/sizeof(arr[0]);
    bubble_sort(arr,sz);
    int i=0;
    for(i=0;i<sz;i++)
    {
        // 增加空格分隔，输出更易读
        printf("%d ",arr[i]);
    }
    return 0;
}