#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ** matrixSpawner(int n){
    int i, j;
    int **matrix = (int**)malloc(sizeof(int*));

    for(i = 0; i < n; ++i){
        matrix[i] = (int*)malloc(sizeof(int));
    }

    for(i = 0 ; i < n ; ++i)
        for(j = 0 ; j < n; ++j)
            matrix[i][j] = 0;

    return matrix;
}

void printMatrix(int **matrix, int n){
    int i,j;
    for(i = 0 ; i < n ; ++i){ 
        for(j = 0 ; j < n; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixWithLetters(int **matrix, int n, char **colors_arr){
    int i,j,z;
    for(i = 0 ; i < n ; ++i){ 
        for(j = 0 ; j < n; j++){
            printf("%s ",colors_arr[matrix[i][j] - 1]);  
        }
        printf("\n");
    }
}

void printShiftCounters(int *shiftArr, int n){
    int i;
    for(i = 0 ; i < n ; ++i){
        printf("%d. Row Rotated %d Times \n", i+1, shiftArr[i]);
    }
}

void shifter(int **matrix, int row, int n){
    int j;
    int tmp,tmp2;

    for(j = 0; j < n ; ++j){
        
        if(j == 0){
            tmp = matrix[row][j];
            matrix[row][j] = matrix[row][n-1];
        }
        else{
        tmp2 = matrix[row][j]; 
        matrix[row][j] = tmp;    
        tmp = tmp2;
        }
    }
}

void arrangerV2(int **matrix, int n, int row, int *shiftCounts){
       
    if(row >= n){
        return;
    } 

    int j = 0, i, in = 1;
    
    if(row != 0){
        
        while(in == 1){
//////////////////////////////////////////////////////////////////////////////////////  INITIAL CONTROL 
//        printf("\n The Row is %d \n", row);    
                for(j = 0 ; j < n ; j++){    // controlling that row's columns
                    
                    if(shiftCounts[row] == n){
//                        printf("\n thats the end\n");
                        return;
                    }
//                    printf("\n IN "); printf("The Row is %d \n", row);
                    for(i = row - 1 ; i >= 0; --i){
                        if(matrix[row][j] == matrix[i][j]){
//                            printf("shift time %d crossing\n", matrix[i][j]);
                            shifter(matrix,row,n);
                            shiftCounts[row] = shiftCounts[row] + 1;
                            j = -1;
                            i = -1; 
                        }                  
                    }

                }
///////////////////////////////////////////////////////////////////////////////////////////////////

            if(row + 1 == n){                  // IF IT IS THE LAST ROW AND HAVE NOT MADE A TOUR THEN BACK
                return;
            }

            arrangerV2(matrix,n,row + 1, shiftCounts);
//////////////////////////////////////////////////////////////////////////////////////////////////
            if(row + 1 != n && shiftCounts[n+1] == n) {
//                printf("\n row below n times round\n");
                shifter(matrix,row,n);
                shiftCounts[row] = shiftCounts[row] + 1;
                shiftCounts[row+1] = 0;

                for(j = 0 ; j < n ; j++){    // controlling that row's columns
                    if(shiftCounts[row] == n){
                        return;
                    }

                    for(i = row - 1 ; i >= 0; --i){

                        if(matrix[row][j] == matrix[i][j]){
                            shifter(matrix,row,n);
                            shiftCounts[row] = shiftCounts[row] + 1;
                            j = -1;
                            i = -1; 
                        }                  
                    }

                }
            }

            if(row + 1 != n && shiftCounts[n+1] != n) {               
                return;
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

    }

    else if(row == 0){                                   // Just for 0. Row

        arrangerV2(matrix , n , row + 1 , shiftCounts);
//        printf("\n val : %d", shiftCounts[row + 1]);
        while(in == 1){
        
            if(shiftCounts[row] == n){
                for(i = 0 ; i < n; ++i)
                    shiftCounts[i] = n;
                printf("There Is No Arrangement Available !\n");
                printf("Your Entered Matrix Would Remain Unchanged\n");
                return;
            }
            
            if(shiftCounts[row + 1] == n){
//                printf("\nget in here\n");
            shifter(matrix,row,n);
            shiftCounts[row] = shiftCounts[row] + 1;
            arrangerV2(matrix , n , row + 1 , shiftCounts);
            }

            else if(shiftCounts[row + 1] != n){
                return;
            }

        }
        
    }
}

int main(){
    int **matrix;
    int n, q = 0 , w = 0;
    int size , i, j, row;
    size = n;

    while(q != 9){
    w = 0;
    printf("Enter 1 to Form a Matrix : \n");    
    printf("Enter 9 to Exit : \n");
    scanf("%d",&q);

    if(q == 1){

        printf("Enter The Size of Board : ");
        scanf("%d",&n);
        int *shiftCounts = (int*)malloc(n * sizeof(int));

        for(i = 0; i < n; ++i)
            shiftCounts[i] = 0;

        matrix = matrixSpawner(n);

        char* color_arr_tmp[n];
        char *color_array[n];
        char color[20];
        
        for(i = 0 ; i < n; ++i)
            color_arr_tmp[i]= (char*)malloc(strlen(color) * sizeof(char));

        for(row = 0 ; row < n; ++row){

            printf("Enter the %d. Rows Colors\n",row + 1);
            for(i = 0 ; i< n ; i++){
                printf("%d. Color : ",i+1);
                scanf("%s", color);
                color_array[i]= (char*)malloc(strlen(color) * sizeof(char));
                strcpy(color_array[i] , color);
                }

            if(row == 0){
                for(i = 0 ; i < n; ++i){
                    strcpy(color_arr_tmp[i],color_array[i]);
                }
            }

            for(i = 0 ; i < n ; ++i){
                for(j = 0 ; j < n ; ++j){
                    if(strcmp(color_array[i],color_arr_tmp[j]) == 0){
                        matrix[row][i] = j+1;
                    }
                }
            }

        }

        while(w != 8){
            printf("Enter 2 to Basic Mode : \n");
            printf("Enter 3 to Detailed Mode : \n");
            printf("Enter 8 to Form a New Matrix or Exit : \n");
            scanf("%d",&w);

            if(w == 2){
                printf("\n-----Before-----\n");
                printMatrixWithLetters(matrix,n,color_arr_tmp);
                printf("\n-----After-----\n");
                arrangerV2(matrix,n,0,shiftCounts);    
                printMatrixWithLetters(matrix,n,color_arr_tmp);
            }
            else if(w == 3){
                printf("\n-----Before-----\n");
                printMatrixWithLetters(matrix,n,color_arr_tmp);
                printf("\n-----After-----\n");
                arrangerV2(matrix,n,0,shiftCounts);    
                printMatrixWithLetters(matrix,n,color_arr_tmp);
                printShiftCounters(shiftCounts,n);
            }


        }

    }

    }

    

    printf("\nfinish");
    return 0;
}
