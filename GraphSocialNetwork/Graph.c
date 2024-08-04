#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct val{
    int value;  
    struct val * next; 
}val;

typedef struct account{
    int order;
    char name[15];
    char sname[15];
    val * conn;
    struct account * below;
    int inDegree;
    int infCounter;
}account;

account* readFile(FILE *fp) {
    char sentence[255];
    char *delim = ",";
    char *ptr;
    int i , conn_head = 1, flag = 0 , flag2 = 1, order_num;
    account * head;

    if (fp == NULL) {
        printf("Couldn't open the file.\n");
    } else {

        account * acc_head = (account*)malloc(sizeof(account));

        while(!feof(fp)) {

            account * acc_tmp = (account*)malloc(sizeof(account));  

            fscanf(fp, "%s\n", sentence);          // taking the whole sentence
            
            ptr = strtok(sentence, delim);        // seperating it from comma
			
            for (i = 0 ; i < 3; i++) {                  // this part for getting accounts  
            
                if(i == 0){                               // It 's assigned to ORDER
                    acc_head->order = atoi(ptr);
                }

                else if(i == 1){                          // It's assigned to NAME
                    strcpy(acc_head->name,ptr);
                }

                else if(i == 2){                         // It's assigned to LNAME               
                    strcpy(acc_head->sname,ptr);
                }

                ptr = strtok(NULL, delim);
            }

            fscanf(fp, "%s\n", sentence);          // taking the whole sentence

            ptr = strtok(sentence, delim);        // seperating it from comma
			

            val * val_head = (val*)malloc(sizeof(val));

            while(ptr != NULL) {                  // this part for getting the account's connections  
                
                    val * val_tmp = (val*)malloc(sizeof(val));
                    val_head->next = val_tmp;

                if(strcmp("\n",ptr) != 0){
                    val_head->value = atoi(ptr);                       
                    ptr = strtok(NULL, delim);
                }
                if(conn_head == 1){                // attach the first follower to account
                    acc_head->conn = val_head;
                    conn_head = 0;
                }
                val_head = val_tmp;
                val_head->next = NULL;
            }
        
            conn_head = 1;

            if(flag == 0){
                head = acc_head;
                flag = 1;
            }      
        acc_head->below = acc_tmp;
        acc_head = acc_tmp;
        acc_head->below = NULL;
        }
    }
    fclose(fp);
    return head;
}

void printLinkedList(account *head){
    account *tmp = head;
    val *tmp_node; 

    while(tmp != NULL){
        printf("%s %s  In-Degree : %d  Total Connections : %d \n",tmp->name,tmp->sname,tmp->inDegree,tmp->infCounter);
        printf("\n");
        tmp = tmp->below;
    }
    printf("\n\n\n");
}

void printLinkedListBasic(account *head){
    account *tmp = head;
    val *tmp_node; 

    while(tmp != NULL){
        printf("%s %s \n",tmp->name,tmp->sname);
        printf("\n");
        tmp = tmp->below;
    }
    printf("\n\n\n");
}

account *trimmed(account *head){
account *tmp = head;
    val *tmp_node;

    while(tmp != NULL){
        if(tmp->below->below == NULL){

            tmp_node = tmp->conn;

            while(tmp_node != NULL){
                if(tmp_node->next->next == NULL){
                    tmp_node->next = NULL;
                    tmp_node = tmp_node->next;
                }
                else{
                    tmp_node = tmp_node->next;
                }
            }
            tmp->below = NULL;
            tmp = tmp->below;
        }
        else{
            tmp_node = tmp->conn;

            while(tmp_node != NULL){
                if(tmp_node->next->next == NULL){
                    tmp_node->next = NULL;
                    tmp_node = tmp_node->next;
                }
                else{
                    tmp_node = tmp_node->next;
                }
            }
            tmp = tmp->below;
        }
    }
    return head;
}

account *find(account *head, int num){
    account *tmp = head;
    while(tmp != NULL){
        if(tmp->order == num){
            return tmp;
        }
        tmp = tmp->below;
    }
    return NULL;
}

account *inDegreeCalc(account *head){
    
    account *tmp = head;
    account *mark;

    while(tmp != NULL){
        tmp->inDegree = 0;
        tmp = tmp->below;
    }
    tmp = head;

    while(tmp != NULL){
        val *tmp_node = tmp->conn;
        while(tmp_node != NULL){
            mark = find(head,tmp_node->value);
            mark->inDegree = mark->inDegree + 1;
            tmp_node = tmp_node->next;
        }
        tmp = tmp->below;
    }
    return head;
}

account *inDegreeElection(account *head , int M){
    account *tmp = head;
    account *back;
    val *tmp_node; 

    while(tmp != NULL){
        tmp_node = tmp->conn;

        if(tmp == head && tmp->inDegree < M){
            head = tmp->below;
            tmp = tmp->below;
        }
        else if(tmp != head && tmp->inDegree < M){
            back->below = tmp->below;
            tmp = tmp->below;
        }
        else{
        back = tmp;    
        tmp = tmp->below;              
        }          
    }
    return head;
}

account *influencerElection(account *head , int Y){
    account *tmp = head;
    account *back;
    val *tmp_node; 

    while(tmp != NULL){
        tmp_node = tmp->conn;

        if(tmp == head && tmp->infCounter < Y){
            head = tmp->below;
            tmp = tmp->below;
        }
        else if(tmp != head && tmp->infCounter < Y){
            back->below = tmp->below;
            tmp = tmp->below;
        }
        else{
        back = tmp;    
        tmp = tmp->below;              
        }          
    }
    return head;
}

int isIt(int num , int *array,int n){
    int i;
    for(i = 0 ; i < n ; i++){
        if(num == array[i])
            return 1;
    }
    return 0;
}

void printArray(int *arr, int n){
    int i;
    for(i = 0 ; i < n ; i++){
       printf("%d ", arr[i]);
    }
    printf("\n");
}

int follower_calc(account* head, int num, int *visited, int index){

    account *finded = find(head,num);

    int n;
    int i;

//    printf("%d  checked if its in visited \n" , num);

    if(isIt(num,visited,30) == 1){
//        printf("%d is in visited so backtrack\n",num);
        return index;
    }

//    printf("%d is not visited so go on  ", num);

//    printArray(visited,10);
////////////////////////////////////////////////////////////  DETECTING DIRECT FOLLOWERS

    int direct_followers[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
    account *tmp = head;
     i = 0;
    while(tmp != NULL){
        val* tmp_node = tmp->conn;
        
        while(tmp_node != NULL){
            if(tmp_node->value == num){
                direct_followers[i++] = tmp->order;
            }
            tmp_node = tmp_node->next;
        }
        tmp = tmp->below;
    } 
///////////////////////////              ARRAY OF DIRECT FOLLOWERS
        for(i = 0 ; i < 30; i++){
        if(direct_followers[i] == 0){
            n = i;
            i = 30;
        }
    }

//////////////////////////////////////////////////////////////////////////////
    
    for(i = 0 ; i < n ; i++){
        if(isIt(direct_followers[i],visited,30) == 0){
            i = n;
        }
        else if(isIt(num,visited,30) == 1 && i == n - 1 && isIt(direct_followers[i],visited,30) == 1){
//            printf("%d followers are all visited so backtrack \n", num);
                return index;
        }
    }
/////////////////////////////////////////////////////////////////////////

    visited[index] = num;
    index++;
/*    printf("\n");

    printf("direct followers of %d are : ",num);
    printArray(direct_followers,n);
    printf("visited nodes are : ");
    printArray(visited,15);
    printf("\n");
*/
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////    FINAL CALL
    for(i = 0; i < n; i++){
        index = follower_calc(head, direct_followers[i],visited,index); 
    }
        return index;
}

account * assign_infPoints(account *head){

    int visited[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    account *tmp;
    int i;

    FILE *fp = fopen("socialNET.txt", "r");
    account* full_head = readFile(fp);

    tmp = head;
    while(tmp != NULL){
        tmp->infCounter = 0;
        tmp = tmp->below;
    }
    tmp = head;

    while(tmp != NULL){

        tmp->infCounter = follower_calc(full_head,tmp->order,visited,0) - 1;

        for(i = 0; i < 30 ; ++i)
            visited[i] = 0;
        
        tmp = tmp->below;
    }

    return head;
}

int main(){

    int instruction = 0;
    int inDegreeLimit = 0;
    int infLimit = 0;

    while(instruction != 9){

        printf("\nEnter In-Degree Limit : ");
        scanf("%d",&inDegreeLimit);
        printf("\n");
        printf("Enter Min Influencer Connection Limit : ");
        scanf("%d",&infLimit);
        printf("\n");

        instruction = 0;
        while(instruction != 8 && instruction != 9){
            printf("Enter 1 to View All Accounts and In-Degree Values\n"); 
            printf("Enter 2 to View Remained Accounts After In-Degree Election\n");
            printf("Enter 3 to View Influencers in Basic Mode \n");
            printf("Enter 4 to View Influencers in Detailed Mode \n");
            printf("Enter 8 to enter new In-Degree and Connection Limits\n");
            printf("Enter 9 to Exit : ");
            scanf("%d", &instruction);

            if(instruction == 1){     // All Accounts and In-Degree Values
                    FILE *fp = fopen("socialNET.txt", "r");
                    account* head = readFile(fp);
                    head = trimmed(head);
                    head = inDegreeCalc(head);
                    head = assign_infPoints(head);
                    printLinkedList(head);
            }
            else if(instruction == 2){ // Remained Accounts After In-Degree Election
                    FILE *fp = fopen("socialNET.txt", "r");
                    account* head = readFile(fp);
                    head = trimmed(head);
                    head = inDegreeCalc(head);
                    head = inDegreeElection(head,inDegreeLimit);
                    head = assign_infPoints(head);
                    printLinkedList(head);
            }
            else if(instruction == 3){ // Influencers
                    FILE *fp = fopen("socialNET.txt", "r");
                    account* head = readFile(fp);
                    head = trimmed(head);
                    head = inDegreeCalc(head);
                    head = inDegreeElection(head,inDegreeLimit);
                    head = assign_infPoints(head);
                    head = influencerElection(head,infLimit);
                    printLinkedListBasic(head);
            }
            else if(instruction == 4){ // Influencers Detailed
                    FILE *fp = fopen("socialNET.txt", "r");
                    account* head = readFile(fp);
                    head = trimmed(head);
                    head = inDegreeCalc(head);
                    head = inDegreeElection(head,inDegreeLimit);
                    head = assign_infPoints(head);
                    head = influencerElection(head,infLimit);
                    printLinkedList(head);
            }

        }

    }
    return 0;
}
