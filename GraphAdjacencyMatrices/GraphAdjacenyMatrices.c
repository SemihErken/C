#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Stack{
    int data;
    struct Stack* next;
}Stack;
 
Stack* newNode(int data)
{
    Stack* stackNode =(Stack*)malloc(sizeof(Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}
 
int isEmpty(Stack* root)
{
    return !root;
}
 
void push(Stack** root, int data)
{
    Stack* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}
 
int pop(Stack** root)
{
    if (isEmpty(*root))
        return INT_MIN;
    Stack* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
 
    return popped;
}
 
int peek(Stack* root)
{
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}


void printMatrix(int **matris,int node_number){
    int i,j;
    printf("   ");
    for(i = 1 ; i< node_number+1;i++)
    printf("%d ",i);

    printf("\n\n");

    for(i = 0 ; i < node_number ; i++){
        printf("%d  ",i+1);        
        for(j = 0 ; j < node_number ;j++)
            printf("%d ",matris[i][j]); 
        printf("\n");
    }
}

int **readFromFile(FILE *fp , int node_number , int **matris){
    int weigh,p1,p2; 
    while(fscanf(fp,"%d %d %d",&weigh,&p1,&p2) == 3){
    matris[p1-1][p2-1] = weigh;
    matris[p2-1][p1-1] = weigh;
    }
    return matris;
}

void dfs(int **matris , int weight , int p1 ,int p2,int node_number){
    int i,j;
    int f1 = p1;
    int f2 = p2;
    Stack* stck = NULL;
    int *visited = (int*)malloc(node_number*sizeof(int));
    for(i = 0 ; i < node_number;i++)
        visited[i] = 0;
    for(i = 0 ; i < node_number ;i++){
        if(matris[i][p1] != 0){
            if(visited[i] == 0){           
                push(&stck,p1);
                p1 = i;
                visited[i] = 1;
                if(i == p2){
                    push(&stck,p1);
                    i = node_number;            
                }
                else
                    i = -1;  
            }
        }
        if((i == node_number-1 && matris[i][p1] == 0) || (i == node_number-1 && matris[i][p1] != 0 && visited[i] != 0)){
            p1 = pop(&stck);
            i = -1;
        }
    }
    
    int tmp1,tmp2,node1,node2,max_length = 0;
    while (stck != NULL){
        node1 = pop(&stck);
        node2 = peek(stck);
        if(matris[node1][node2] > max_length){
            max_length = matris[node1][node2];
            tmp1 = node1;
            tmp2 = node2;
        }
    }

    if(weight < max_length){
        matris[tmp1][tmp2] = 0;
        matris[tmp2][tmp1] = 0;
        matris[f1][f2] = weight;
        matris[f2][f1] = weight; 
    }
//    printf("max length : %d between %d and %d\n\n",max_length,tmp1+1,tmp2+1);
}

int main(){

    int i,j,weight,p1,p2,node_number, choice;

    FILE *fp;
    fp = fopen("Sample_MST.txt","r");
    if(fp == NULL){
        printf("couldnt opened");
        exit(1);
    }

    printf("Enter The Node Number : ");
    scanf("%d",&node_number);
        
    int *matris[node_number];
    for(i = 0 ; i < node_number ; i++)
        matris[i] = (int*)malloc(node_number*sizeof(int));


    for(i = 0 ; i < node_number ; i++)        
        for(j = 0 ; j < node_number ;j++)
            matris[i][j] = 0; 

    readFromFile(fp,node_number,matris);


    while(choice != 9){

        printf("\n1 - Print Matrix : \n\n2 - Add Connection Between Two Nodes : \n\n9 - Exit : ");
        scanf("%d",&choice);
        if(choice == 1){
            printMatrix(matris,node_number);
        }
        else if(choice == 2){
            printf("Enter the Length of Connection : ");
            scanf("%d",&weight);
            printf("Enter the First Node : ");
            scanf("%d",&p1);
            printf("Enter the Second Node : ");
            scanf("%d",&p2);
            dfs(matris,weight,p1-1,p2-1,node_number);
        }
    }
    fclose(fp);
    return 0;
}