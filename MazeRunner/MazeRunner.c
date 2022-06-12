#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <Windows.h>

#define MAX_LINE_LENGTH 100

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
////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void print_maze(int **matrix , int line_count , int line_length , int point , int crash , int EatenApple){
    sleep(0.1);
    system("cls");
	int i = 0 , j = 0;
    printf("POINTS : %d CRASH : %d EATEN APPLES : %d\n" ,point , crash , EatenApple);
    for(i = 0 ; i < line_count ; i++){

        int indicator_row = i % 2;

        for(j = 0 ; j < line_length; j++){
            
            int indicator_colomn = j % 2;

            if(indicator_row == 0){

                if(indicator_colomn == 0){
                    if(matrix[i][j] == 0)
                        printf("+");
                    else if(matrix[i][j] == 2)
                        printf("O");
                    else
                        printf(" ");    
                }
                else{
                    if(matrix[i][j] == 0)
                        printf("-");
                    else if(matrix[i][j] == 2)
                        printf("O");
                    else
                        printf(" ");    
                }
                    
            }
            else{

                if(matrix[i][j] == 0)
                    printf("|");
                else if(matrix[i][j] == 2)
                    printf("O");
                else if(matrix[i][j] == 1)
                    printf(" ");
                else if(matrix[i][j] == 4)
                    printf(" ");    
                else if(matrix[i][j] == 3)
                    printf("*");      
            }
        }

        printf("\n");
    }

}

void print_matrix(int **matrix,int line_count ,int line_length){
    int i = 0 , j = 0;  
    for(i = 0 ; i < line_count ; i++){
        
        if(i < 10)
        printf("%d  : ",i);
        else
        printf("%d : ",i);
        for(j = 0 ; j < line_length ; j++)
            printf("%d",matrix[i][j]);

        printf("\n");
    }
}


int main(){    
    FILE *read_maze;
    char line_counter[MAX_LINE_LENGTH] = {0};
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;
    int line_length = 0;
    Stack* stckRow = NULL;
    Stack* stckColumn = NULL;

    read_maze = fopen("maze.txt","r");
    line_count = 0;
    line_length = 0;


    if(read_maze == NULL){
        printf("File Couldn't Opened");
        exit(1);
    }


    while (fgets(line_counter, MAX_LINE_LENGTH, read_maze)) {
        ++line_count;
        
    }
    line_length = strlen(line_counter) - 1;

    printf("Line Count : %d Line Length : %d\n",line_count,line_length);

    fclose(read_maze);


    read_maze = fopen("maze.txt","r");

    int* matrix[line_count];
	
	int z ;
    for (z = 0; z < line_count; z++)                                    // CREATING  MATRIX
        matrix[z] = (int*)malloc(line_length * sizeof(int));


    int i = 0;

    while (fgets(line, MAX_LINE_LENGTH, read_maze)) {
        
        int a;
        for(a = 0 ; a < line_length ; a++){
            if(line[a] == '-' || line[a] == '+' || line[a] == '|'){
                matrix[i][a] = 0;
            }
            else{
                matrix[i][a] = 1;
            }
        }
        ++i;   
    }


    
int locatedApple = 0;
    
        srand(time(NULL));
    while(locatedApple < 15){

        int random_row = rand() % line_count;
        int random_colomn = rand() % line_length;

        if(matrix[random_row][random_colomn] != 0){
            if(matrix[random_row][random_colomn-1] != 2 & matrix[random_row][random_colomn+1] != 2 & matrix[random_row-1][random_colomn] != 2 & matrix[random_row+1][random_colomn] != 2){
                matrix[random_row][random_colomn] = 2;
                ++locatedApple;
            }

        }
    }
    
    int startRow = 1;
    int startColoumn = 1;
    int currentRow = startRow;
    int currentColumn = startColoumn; 
    int destinationRow = line_count - 2 ;
    int destinationColumn = line_length - 2 ;

    int point = 0;
    int eatenApples = 0;
    int crash = 0;
    int step = 0;
    printf("dest_row : %d dest_col : %d\n" , destinationRow,destinationColumn);
    while(!(currentColumn == destinationColumn && currentRow == destinationRow)){
        print_maze(matrix,line_count,line_length , point , crash , eatenApples);
        step++;

        if(matrix[currentRow+1][currentColumn] == 1 || matrix[currentRow+1][currentColumn] == 2){                       //  CHECKING DOWN
//                printf("Step : %d MOVE DOWN [%d][%d] \n" , step,currentRow,currentColumn);                                                                                                       
                matrix[currentRow][currentColumn] = 3;
                push(&stckRow,currentRow);
                push(&stckColumn,currentColumn);
                currentRow++;

                if(matrix[currentRow][currentColumn] == 2){
                    point = point + 10;
                    eatenApples++;
                }
                    
        }
        else if(matrix[currentRow][currentColumn+1] == 1 || matrix[currentRow][currentColumn+1] == 2){                  //   CHECKING RIGHT
//                printf("Step : %d MOVE RIGHT [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 3;
                push(&stckRow,currentRow);
                push(&stckColumn,currentColumn);
                currentColumn++;

                if(matrix[currentRow][currentColumn] == 2){
                    point = point + 10;
                    eatenApples++;
                } 
        }
        else if(matrix[currentRow][currentColumn-1] == 1 || matrix[currentRow][currentColumn-1] == 2){                  //   CHECKING LEFT
//                printf("Step : %d MOVE LEFT [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 3;
                push(&stckRow,currentRow);
                push(&stckColumn,currentColumn);
                currentColumn--;

                if(matrix[currentRow][currentColumn] == 2){
                    point = point + 10;
                    eatenApples++;
                }
        }

        else if(matrix[currentRow-1][currentColumn] == 1 || matrix[currentRow-1][currentColumn] == 2){                  //   CHECKING UP
//                printf("Step : %d MOVE UP [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 3;
                push(&stckRow,currentRow);
                push(&stckColumn,currentColumn);
                currentRow--;

                if(matrix[currentRow][currentColumn] == 2){
                    point = point + 10;
                    eatenApples++;
                }
        }


        else if(matrix[currentRow+1][currentColumn] == 3){                  //   CHECKING DOWN FOR BACK
//                printf("Step : %d BACK DOWN [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 4;
                currentRow = pop(&stckRow);
                currentColumn = pop(&stckColumn); 
        }

        else if(matrix[currentRow][currentColumn+1] == 3){                  //   CHECKING RIGHT FOR BACK
//                printf("Step : %d BACK RIGHT [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 4;
                currentRow = pop(&stckRow);
                currentColumn = pop(&stckColumn); 
        }

        
        else if(matrix[currentRow][currentColumn-1] == 3){                  //   CHECKING LEFT FOR BACK
//                printf("Step : %d BACK LEFT [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 4;
                currentRow = pop(&stckRow);
                currentColumn = pop(&stckColumn); 
        }

        else if(matrix[currentRow-1][currentColumn] == 3){                  //   CHECKING UP FOR BACK
//                printf("Step : %d BACK UP [%d][%d]\n" , step,currentRow,currentColumn); 
                matrix[currentRow][currentColumn] = 4;
                currentRow = pop(&stckRow);
                currentColumn = pop(&stckColumn); 
        }

        if(matrix[currentRow+1][currentColumn] != 1 && matrix[currentRow-1][currentColumn] != 1 && matrix[currentRow][currentColumn+1] != 1 && matrix[currentRow][currentColumn-1] != 1)
         {
             if(matrix[currentRow+1][currentColumn] != 2 && matrix[currentRow-1][currentColumn] != 2 && matrix[currentRow][currentColumn+1] != 2 && matrix[currentRow][currentColumn-1] != 2)
            {
                if(matrix[currentRow+1][currentColumn] != 4 && matrix[currentRow-1][currentColumn] != 4 && matrix[currentRow][currentColumn+1] != 4 && matrix[currentRow][currentColumn-1] != 4)
                {
                    crash++;
                    point = point - 5;
                }
            }
         }             

    }


//    print_matrix(matrix,line_count,line_length);

    printf("\n Returned with 0 value");
    return 0;
}
