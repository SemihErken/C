#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node{
    int first_Index;
    int last_Index;
    int val;
}node;

node* find_max(node *x, node* y) {
    if(x->val > y->val)
        return x;
    else
        return y;
}
 
node* max_range(int area[], int low, int high)
{
    if (high <= low) {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->val = area[low];
        newNode->first_Index = low;
        newNode->first_Index = high; 
        return newNode;
    }
    int mid = (low + high) / 2;
    node *left_half_max = (node*)malloc(sizeof(node));
    left_half_max->val = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum += area[i];
        if (sum > left_half_max->val) { 
            left_half_max->val = sum;
            left_half_max->first_Index = i;
            left_half_max->last_Index = mid;
        }
    }
 
    node *right_half_max = (node*)malloc(sizeof(node));
    right_half_max->val = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++)
    {
        sum += area[i];
        if (sum > right_half_max->val) {
            right_half_max->val = sum;
            right_half_max->first_Index = mid+1;
            right_half_max->last_Index = i;
        }
    }
 
    node* max_left_right_decide = (node*)malloc(sizeof(node));
    max_left_right_decide = find_max(max_range(area, low, mid),max_range(area, mid + 1, high));
 
    node *sum_of_right_left_halfs = (node*)malloc(sizeof(node));
    sum_of_right_left_halfs->val = left_half_max->val + right_half_max->val;
    sum_of_right_left_halfs->first_Index = left_half_max->first_Index;
    sum_of_right_left_halfs->last_Index = right_half_max->last_Index;
    return find_max(max_left_right_decide, sum_of_right_left_halfs);
}
 
int main(void)
{
    int area[] = { 8, 30, 3 ,-26, -6, 52, 8, -1, 11, 10, 4, -5};
    int n = sizeof(area) / sizeof(area[0]);
 
    printf("%d to %d Max Value Is : %d",max_range(area , 0 , n-1)->first_Index, max_range(area , 0 , n-1)->last_Index, max_range(area , 0 , n-1)->val);

    return 0;
}
