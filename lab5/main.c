#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>


#define MAX 100000

int arr[MAX];
int tmp[MAX];
bool isMulti = false;

typedef struct {
    int left;
    int right;
} args;

void merge(int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]){
            tmp[k++] = arr[i++];
        }
        else{
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid){
        tmp[k++] = arr[i++];
    }
    while (j <= right){
        tmp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++){
        arr[i] = tmp[i];
    }
}

void *merge_sort(void *arg)
{
    args *targ = (args*)arg;
    int left = targ->left;
    int right = targ->right;
    if (left >= right){
        return NULL;
    }
    int mid = (left + right) / 2;
    if (right - left < 1000) { // если размер массива меньше 1000, сортируем последовательно
        for (int i = left + 1; i <= right; i++) {
            int j = i - 1;
            int key = arr[i];
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    } else { // иначе делаем рекурсивный вызов в новых потоках
        pthread_t thread1, thread2;
        args arg1 = {left, mid};
        args arg2 = {mid + 1, right};
        pthread_create(&thread1, NULL, merge_sort, &arg1);
        pthread_create(&thread2, NULL, merge_sort, &arg2);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        merge(left, mid, right);
    }
    return NULL;
}

int main()
{
    struct timeval start, end;
    long mtime, secs, usecs;
    srand(time(NULL));
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    gettimeofday(&start, NULL);

    args arg = {0, n - 1};
    merge_sort(&arg);

    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;
    printf("Elapsed time: %ld millisecs\n", mtime);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}