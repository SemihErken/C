#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int first_Index;
    int last_Index;
    int val;
    struct node* next;
}node;

int main(){
    int n;
    printf("Enter the How Many Elements You Will Enter : ");
    scanf("%d",&n);
    int* area = (int*)malloc(n*sizeof(int)); 

    int a; for(a = 0; a < n; a++){
        printf("%d. Element : ",a+1);
        scanf("%d",&area[a]);
    }

    int max_Val_node , first , last;
 
    node* values = (node*)malloc(sizeof(node));
    node *head = values;    
    int max_Val = 0 , counter = 0;
 
    int i; for(i = 1; i <= n ; i++){
        int j; for(j = 0; j < n - i + 1 ; j++){
            int k; for(k =  j ; k <= j + i - 1 ; k++){
                max_Val = max_Val + area[k];
            }
            node *temp = (node*)malloc(sizeof(node));
            temp->first_Index = j;
            temp->last_Index = j + i - 1;
            temp->val = max_Val;
            temp->next = NULL;
            values->next = temp;
            values = temp;
            max_Val = 0;
        }
    }
    node*temp = head->next;
    max_Val_node = temp->val; 
    while(temp != NULL){
       if(temp->val > max_Val_node){
            max_Val_node = temp->val;
            first = temp->first_Index;
            last = temp->last_Index;
       }
        temp = temp->next;
    }
    printf("First Index : %d Last Index : %d Max Value : %d", first ,last ,max_Val_node);
    return 0; 
}
