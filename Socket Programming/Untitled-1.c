#include<stdio.h>

int partition (int A[], int l, int h)
{
    int pivot=A[l];
    int i=l;
    int j=h;
    do{
        do{
            i++;
        }while(A[i]<=pivot);
        do{
            j--;
        }while(A[j]>pivot);
        if (i<j){
            int temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
    }while(i<j);
    
    int temp=A[j];
    A[j]=A[l];
    A[l]=temp;

    return j;
}

void QuickSort(int A[], int l, int h)
{
    int j;
    if (l<h)
    {
        j=partition(A,l,h);
        QuickSort(A,l,j);
        QuickSort(A,j+1,h);
    }
}

int main()
{
    int A[]={11,13,7,12,16,9,24,100};

    QuickSort(A,0,7);
    for (int i=0; i<8; i++)
    {
        printf("%d", A[i]);
        printf("\n");
    }

    return 0;
}