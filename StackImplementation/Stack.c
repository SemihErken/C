#include <stdio.h>
#include <stdlib.h>

int isEmpty(int *top){
   if(*top == -1)
      return 1;
   else
      return 0;
}

int isFull(int size,int *top){
   if(*top == size)
      return 1;
   else
      return 0;
}

char peek(char *Stack,int *top){
   return Stack[*top];
}

char pop(int *top){
   if(!isEmpty(top))
      *top = *top-1;
   else
      printf("Could not retrieve data, Stack is empty.\n");
}

char push(char data, int size ,char *Stack ,int *top){
   if(!isFull(size,top)){
      *top = *top+1;   
      Stack[*top] = data;
   } 
   else{
      printf("Could not insert data, Stack is full.\n");
   }
}

int conversion(int size, long long number, char* string){
    int i, k;
    for(i = size-1; i >= 0; i--){
        k = number >> i;
        if(k & 1){
            string[i] = '1';
        }
        else{
            string[i] = '0';
        }
    }
}
int main(){
    int number, i, size;
    char* string;

    int a = -1;
    int *top;
    char Stack[32];
    top = &a;

	printf("Enter Number : ");
    scanf("%d", &number);

    if(number >= -128 && number <= 127)
        size = 8;

    else if(number >= -32768 && number <= 32767)
        size = 16;

    else if(number >= -21474483648 && number <= 21474483647)
        size = 32; 

    else{
        printf("\nEnter less than 32 bits Number Please.");
        return 0;
    }
    string = (char*)malloc(size * sizeof(char));
    conversion(size, number, string);
    printf("Your Number's Binary Conversion : ");
    for(i = size - 1 ; i >= 0; i--){
	    printf("%c",string[i]);
    }

    for(i = 0; i < size; i++){
        if(*top == -1)
            push(string[i], size, Stack ,top);
        else if(Stack[*top] == string[i])
            push(string[i], size, Stack , top);
        else
            pop(top);
    }
    if(*top == -1)
        printf("\n0's and 1's are equal ");
    
    else if(peek(Stack,top) == '0')
        printf("\n0's are more , %d more 1 is needed.",*top+1);
    
    else
        printf("\n1's are more , %d more 0 is needed.",*top+1);

	return 0;
}