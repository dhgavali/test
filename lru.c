#include <stdio.h>

int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++) {
        printf("Enter %d: ",i+1);
        scanf("%d",&arr[i]);
    }
   
    int frame;
    printf("Enter frame size: ");
    scanf("%d",&frame);
   
    int index = 0;
    int frameStack[frame];
    int fcount[frame];   
    for(int i=0;i<frame;i++) {
        frameStack[i] = -1;
        fcount[i] = 0;
    }
   
    int count = 0;
   
    for(int i=0;i<n;i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
   
    for(int i=0;i<n;i++) {
        int num = arr[i];
        int flag = 0;
        for(int j=0;j<frame;j++) {
            if(frameStack[j] == num) {
                flag = 1;
                break;
            }
        }
        for(int j=0;j<frame;j++) {
            fcount[j] = fcount[j] + 1;
        } 
        if(flag == 1) {
            for(int f=0;f<frame;f++) {
                if(frameStack[f] == num) {
                    fcount[f] = 0;
                }
            }
            for(int j=0;j<frame;j++) {
                if(frameStack[j] == -1) {
                    printf("* ");
                }
                else {
                    printf("%d ",frameStack[j]);
                }
            }
            printf("\n");
            continue;
        }
        else {
            count++;
            int max = -1,x;
            for(int p=0;p<frame;p++) {
                if(fcount[p] > max) {
                    max = fcount[p];
                    x = p;
                } 
            }
            frameStack[x] = num;
            fcount[x] = 0;
        }
       
        for(int j=0;j<frame;j++) {
            if(frameStack[j] == -1) {
                printf("* ");
            }
            else {
                printf("%d ",frameStack[j]);
            }
           
        }
        printf("\n");
    }
    float tCount = count;
    float num = n;
    printf("Number of page fault: %d\n",count);
    float freq = (tCount/num)*100;
    printf("Page fault frequency is : %f",freq);
    return 0;
}




/*output
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 
7 * * * 
7 0 * * 
7 0 1 * 
7 0 1 2 
7 0 1 2 
3 0 1 2 
3 0 1 2 
3 0 4 2 
3 0 4 2 
3 0 4 2 
3 0 4 2 
3 0 4 2 
3 0 4 2 
3 0 1 2 
3 0 1 2 
3 0 1 2 
3 0 1 2 
7 0 1 2 
7 0 1 2 
7 0 1 2 
Number of page fault: 8
Page fault frequency is : 40.000000*/
