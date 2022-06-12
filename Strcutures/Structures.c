#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *below;
    int order;
    int floor;
}node;

typedef struct HardNode{
    struct Node *next;
    struct HardNode *below;
}hnode;

int NodeFinderOrder(hnode *root,int order){
    node *iter; 
    iter = root->next;
    while(iter != NULL){
        if(iter->order == order){
            return iter->data;
        }
        iter = iter->next;
    }
}

node *NodeFinderValue(hnode *root,int data){
    node *iter; 
    iter = root->next;
    while(iter != NULL){
        if(iter->data == data){
            return iter;
        }
        iter = iter->next;
    }
}

node *search(hnode *root,int wanted){
    hnode *tmp_root;
    node *iter;
    tmp_root = root;
    while(tmp_root != NULL){    
        if(wanted < tmp_root->next->data){
        tmp_root = tmp_root->below;
        }
        else if(wanted > tmp_root->next->data){
            iter = tmp_root->next;
            while(iter != NULL){
                if(iter->next != NULL){
                    if(wanted > iter->next->data){
                        iter = iter->next;
                    }
                    else if(wanted < iter->next->data){
                        if(iter->below != NULL){
                        iter = iter->below;
                        }
                        else if(iter->below == NULL){
                            printf("There Is No Value %d In Linked Lists\n", wanted);
                            return iter;
                        }
                    }
                    else if(wanted == iter->next->data){
                        iter = iter->next;
                        if(iter->below !=NULL){
                            printf("%d Founded in Layer : %d",iter->data,iter->floor);
                            while(iter->below != NULL){
                                iter = iter->below;
                            }
                            return iter;
                        }
                        else if(iter->below == NULL){
                            printf("%d Founded in Layer : %d\n",iter->data,iter->floor);
                            return iter;
                        }
                    }
                }
                else if(iter->next == NULL){
                    if(iter->below == NULL){
                        printf("There Is No Value %d In Linked Lists\n", wanted);
                        return iter;
                    }
                    else{
                    iter = iter->below;
                    }
                }
            }
        }
        else{
            iter = tmp_root->next;
            printf("%d Founded in Layer : %d",iter->data,iter->floor);
            while(iter->below != NULL){
                iter = iter->below;
            }
            return iter;
        }
    }
    printf("There Is No Value %d In Linked Lists\n", wanted);
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
  
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}

void LastNodeDestroyer(hnode *root){
    node *iter; 
    iter = root->next;
    node *delete;
    while(iter != NULL){
        if(iter->next->next == NULL){
            free(iter->next->next);
            iter->next = NULL;
        }
        iter = iter->next;
    }
}

node *lastNode(hnode *root){
    node *iter; 
    iter = root->next;
    while(iter->next != NULL){
        iter = iter->next;
    }
    return iter;
}

node *create_layer_Node(){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->next = NULL;
    new_node->order = -1;
    return new_node;
}

hnode *create_hardNode(){
    hnode *new_node = (hnode*)malloc(sizeof(hnode));
    new_node->next = NULL;
    return new_node;        
}

node *AddNode(hnode *root , int selected){
    hnode *tmp_root;
    node *iter;
    node *new;
    node *tmp;
    tmp_root = root;
    while(tmp_root != NULL){    
        if(selected < tmp_root->next->data){
            if(tmp_root->below != NULL){
            tmp_root = tmp_root->below;
            }
            else if(tmp_root->below == NULL){
                new = create_layer_Node();
                new->order = 0;
                new->data = selected;
                new->floor = 1;
                new->below = NULL;
                iter = tmp_root->next;
                new->next = iter;
                tmp_root->next = new;
                while(iter != NULL){
                    iter->order = iter->order + 1;
                    iter = iter->next;
                }
                return iter;
            }    
        }
        else if(selected > tmp_root->next->data){
            iter = tmp_root->next;
            while(iter != NULL){
                if(iter->next != NULL){
                    if(selected > iter->next->data){
                        iter = iter->next;
                    }
                    else if(selected < iter->next->data){
                        if(iter->below != NULL){
                        iter = iter->below;
                        }
                        else if(iter->below == NULL){
                            new = create_layer_Node();
                            new->order = iter->order + 1;
                            new->data = selected;
                            new->floor = 1;
                            new->next = iter->next;
                            iter->next = new;
                            tmp = new->next;
                            while(tmp != NULL){
                                tmp->order = tmp->order + 1;
                                tmp = tmp->next;
                            }
                            return iter;
                        }
                    }
                    else if(selected == iter->next->data){
                        iter = iter->next;
                        if(iter->below !=NULL){
                            while(iter->below != NULL){
                                iter = iter->below;
                            }
                            new = create_layer_Node();
                            new->order = iter->order + 1;
                            new->data = selected;
                            new->floor = 1;
                            new->next = iter->next;
                            iter->next = new;
                            tmp = new->next;
                            while(tmp != NULL){
                                tmp->order = tmp->order + 1;
                                tmp = tmp->next;
                            }

                            return iter;
                        }
                        else if(iter->below == NULL){
                            new = create_layer_Node();
                            new->order = iter->order + 1;
                            new->data = selected;
                            new->floor = 1;
                            new->next = iter->next;
                            iter->next = new;
                            tmp = new->next;
                            while(tmp != NULL){
                                tmp->order = tmp->order + 1;
                                tmp = tmp->next;
                            }
                            return iter;
                        }
                    }
                }
                else if(iter->next == NULL){
                    if(iter->below == NULL){
                        new = create_layer_Node();
                        new->order = iter->order + 1;
                        new->data = selected;
                        new->floor = 1;
                        iter->next = new;
                        tmp = new->next;
                        while(tmp != NULL){
                            tmp->order = tmp->order + 1;
                            tmp = tmp->next;
                        }
                        return iter;
                    }
                    else{
                    iter = iter->below;
                    }
                }
            }
        }
        else{
            iter = tmp_root->next;
            while(iter->below != NULL){
                iter = iter->below;
            }
            new = create_layer_Node();
            new->next = iter->next;
            iter->next = new;
            new->data = selected;
            new->floor = 1;
            new->order = iter->order + 1;
            tmp = new->next;
            while(tmp != NULL){
                tmp->order = tmp->order + 1;
                tmp = tmp->next;
            }
            return iter;
        }
    }
}

int DeleteNode(hnode *root , int wanted){
    hnode *tmp_root;
    node *tmp;
    node *prew;
    tmp_root = root;
    while(tmp_root->below != NULL){
        tmp_root = tmp_root->below;
    }
    tmp = tmp_root->next;
    prew = tmp_root->next;
    while(tmp != NULL){
        if(tmp_root->next->data == wanted){
            tmp_root->next = tmp->next;
            prew = tmp;
            tmp = tmp->next;
            free(prew);
            while(tmp != NULL){
                tmp->order = tmp->order - 1;
                tmp = tmp->next;
            }
        }
        else{
                while(tmp != NULL){
                if(tmp->data == wanted){
                    prew->next = tmp->next;
                    free(tmp);
                    tmp = prew->next;
                    while(tmp != NULL){
                        tmp->order = tmp->order - 1;
                        tmp = tmp->next;
                    }
                    return 1;
                }
                prew = tmp;
                tmp = tmp->next;
            }
        }
    }
}

int array_checker(int *array , int num){
    int i = 0;
    for(i = 0; i < 10 ; i++)
    {
        if(num == array[i])
            return 1;
    }
    return 0;
}

hnode *create_layer(hnode *head,int counter,int i){
    int prew_counter;
    int random_number;
    int floor = 2;
    int z = 0;
    int selected_number;
    int *selected_ones = (int*)malloc(sizeof(int));
    node *new_Node;
    hnode *floor_Node;
    node *tmp;
    hnode *tmp_floor;

    while(counter != 1){
        prew_counter = counter;
        counter = (counter + 1) / 2 ;
        floor_Node = create_hardNode();
        new_Node = create_layer_Node();
        floor_Node->next = new_Node;
        int array[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        for(i = 0 ; i < counter ; i++){
            while(1){
            random_number = rand()%prew_counter;
            if(array_checker(array,random_number) == 0){
                break;
            }
        }   
            selected_ones[i] = NodeFinderOrder(head,random_number);
            selected_ones = realloc(selected_ones,(i+2) * sizeof(int));
            array[i] = random_number;
        }
        selectionSort(selected_ones,counter);

        for(i=0 ;i < counter ;i++){
                    new_Node->data = selected_ones[i];
                    new_Node->order = i;
                    new_Node->floor = floor;
                    tmp = create_layer_Node();
                    new_Node->next = tmp;
                    new_Node->below = NodeFinderValue(head,selected_ones[i]);
                    new_Node = tmp;
            }
            LastNodeDestroyer(floor_Node);
            floor_Node->below = head;
            head = floor_Node;
            printf("\n");
        floor++;  
        }
        free(selected_ones);
        return head;
    }

void printAll(hnode *root){
    hnode *tmp_root;
    node *iter;
    tmp_root = root;
    printf("\n\n\n");
    while(tmp_root != NULL)
    {
        iter = tmp_root->next;
        while(iter != NULL){
            printf("%d   ",iter->data);
            iter = iter->next;
        }
        printf("\n");
        tmp_root = tmp_root->below;
    }
}

void FreeAll(hnode *root){
    node *iter;
    node *delete;
    hnode *hdelete;
    while(root != NULL)
    {
        iter = root->next;
        while(iter != NULL){
            delete = iter;
            iter = iter->next;
            free(delete);
        }
        printf("\n");
        hdelete = root;
        root = root->below;
        free(hdelete);
    }
}

int main (){
    int i;
    int choice = 0;
    int num;
    int wanted;
    int adding;
    int  *entered_nums = (int*)malloc(sizeof(int*));
    hnode *root = (hnode*)malloc(sizeof(hnode));
    node *head;
    node *iter;
    node *new;
    hnode *upmost;
    node *tmp;
    node *first;

    srand(time(NULL));
    int counter = 0;

    while(choice != 9){

        printf("\n1 to Create Array : \n2 to Add Node : \n3 to Delete Node : \n4 to Search Node : \n5 to List Nodes : \n9 to Exit  \n");
        scanf("%d",&choice);
        
        if(choice == 1){
            printf("Enter the Array's Elements Number : ");
            scanf("%d",&counter);

            for(i = 0 ; i < counter ;++i){
                printf("Enter The %d. Element : ",i+1);
                scanf("%d", &num);
                entered_nums[i] = num;
                entered_nums = realloc(entered_nums,(i+2) * sizeof(int));           
            }

            selectionSort(entered_nums,counter);
                root->next = iter;
                iter = (node*)malloc(sizeof(node));
                iter->data = entered_nums[0];
                iter->order = 0;
                iter->floor = 1;
                iter->below = NULL;
                root->next = iter;

            for(i = 1 ; i < counter ; i++){
                new = (node*)malloc(sizeof(node));
                new->data = entered_nums[i];
                new->order = i;
                new->floor = 1;
                new->below = NULL;

                iter->next = new;
                iter = iter->next;
                iter->next = NULL;      
        }
                root->below = NULL;
            upmost = create_layer(root,counter,i);
        }
        else if(choice == 2){
            printf("How Many Nodes You Want to Add : ");
            scanf("%d",&adding);
            for(i = 0 ; i < adding ; ++i){
                printf("Enter the Value : ");
                scanf("%d",&num);
                AddNode(upmost,num);
                counter++;
                upmost = create_layer(root,counter,i);
            }
        }
        else if(choice == 3){
            printf("Enter the Number You Want to Delete : ");
            scanf("%d",&adding);
            DeleteNode(upmost,adding);
            counter--;
            upmost = create_layer(root,counter,i);
        }
        else if(choice == 4){
            printf("Enter the Number You Want To Search : ");
            scanf("%d",&wanted);
            search(upmost,wanted);
        }
        else if(choice == 5){
            printAll(upmost);
        }
    }
    
    free(entered_nums);
    FreeAll(upmost);
    return 0;
}