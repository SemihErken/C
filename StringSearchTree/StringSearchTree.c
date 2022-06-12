#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 15

typedef struct list{
    char file_name[10];
    struct list *next;
}list;

typedef struct node{
    char word[20];  
    list *files_list;
    struct node *right;
    struct node *left;
}node;

list *listCreator(){
    list *new_list = (list*)malloc(sizeof(list));
    new_list->next = NULL;
    return new_list;
}

node *nodeCreator(){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->files_list = NULL;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

list *addFileName(list *root , char *text){
    list *iter = root;
    list *prev , *tmp;

    if(iter == NULL){
        iter = listCreator();
        strcpy(iter->file_name,text);
        return iter;
    }
    else{
        for(tmp = iter; tmp != NULL; tmp = tmp->next){prev = tmp;};
        tmp = listCreator();
        strcpy(tmp->file_name,text);
        prev->next = tmp;
        return root;
    } 
}

node *addNode(node *root, char *wanted ,char *text){
    list *tmp;
    node *iter = root; 
    if(iter == NULL){
        iter = nodeCreator();
        strcpy(iter->word,wanted);
        iter->files_list = addFileName(iter->files_list,text);
        return iter;
    }
    if(strcmp(iter->word,wanted)>0){
        iter->left = addNode(iter->left,wanted,text);
    }
    else if(strcmp(iter->word,wanted)<0){
        iter->right = addNode(iter->right,wanted,text);
    }
    else if(strcmp(iter->word,wanted) == 0){
        iter->files_list = addFileName(iter->files_list,text);
        return iter;
    }
    return iter;
}

node *readFromFile(FILE *fp , char *text_name , node *root){
    char *word = (char*)malloc(SIZE * sizeof(char));
    node *word_cell; 
    while(fscanf(fp,"%s",word) == 1){
        root = addNode(root,word,text_name);
//        printf("%s ",word);
    }
    return root;
}

void printTree(node *root){
    node *iter = root;
    if(iter == NULL){
        return;
    }
    printTree(iter->left);
    printf("%s ",iter->word);
    printTree(iter->right);
}

node *searchTree(node *root , char *wanted){
    node *iter = root;
    if(iter == NULL){
        printf("There Is No Word Named : %s\n",wanted);
        return root;
    }
    else{
        if(strcmp(iter->word,wanted) == 0){
             printf("%s\n",iter->word);
            while(iter->files_list != NULL){
                printf("%s\n",iter->files_list->file_name);
                iter->files_list = iter->files_list->next;
            }
            return root;
        }
        else if(strcmp(iter->word,wanted) > 0){
            iter->left = searchTree(iter->left , wanted);
        }
        else if(strcmp(iter->word,wanted) < 0){
            iter->right = searchTree(iter->right , wanted);
        }
    }
}
/*
void deleteNode(node **root_ptr , char *text_name){
    node *root = *root_ptr;  
    if(root == NULL) return;

    deleteNode(root->left,text_name);
    list *iter = root->files_list;
    list *prev = NULL; 
    list *tmp;
    while(iter != NULL){
        if(strcmp(iter->file_name,text_name) != 0){
            prev = iter;
            iter = iter->next;
        }
        else{
            if(iter->next != NULL){
                if(prev == NULL){
                    root->files_list = iter->next;
                    free(iter);
                    return;
                }
                else{
                    prev->next = iter->next;
                    free(iter);
                    return;
                }
            }
            else{
                if(prev == NULL){
                    free(iter);
                    root->files_list = NULL;
                    return;
                }
                else{
                    prev->next = iter->next;
                    free(iter);
                    return;
                }
            }
        } 
    }
    deleteNode(root->right,text_name);
}
*/


int main(){
    FILE *fp;
    node *root = NULL;
    char text_name[10]; 
    int choice = 0;
    char wanted[20];
    
    while(choice != 9){

        printf("\n1 - Add New Files : \n2 - Search Word : \n3 - Delete File : \n4 - Print Tree : \n9 - Exit : ");
        scanf("%d",&choice);

        if(choice == 1){
            printf("Enter the File Name You Want to Add : ");
            scanf("%s",text_name);
            fp = fopen(text_name, "r");
            if (fp == NULL){
                printf("\nFile Couldn't Opened !\n");
                return 0;
            }
            root = readFromFile(fp , text_name, root);
            fclose(fp);
        }
        else if(choice == 2){
            printf("Enter the Word You Want to Search : ");
            scanf("%s",wanted);
            searchTree(root,wanted);
        }
        else if(choice == 3){
            printf("Enter the Word You Want to Delete : ");
            scanf("%s",wanted);
//            deleteNode(root,wanted);
        }
        else if(choice == 4){
            printTree(root);
        }
    }
}