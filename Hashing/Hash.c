#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each linked list node that holds the websites
struct Node {
	char *value;
	struct Node *next;
};

// Each hashtable cell
struct Key {
    char *key;
    struct Node *values;
};


struct HashTable {
    struct Key *arr;
    int size;
    int count;
};

// Returns the list of websites that have the given keyword 
struct Node *findSites(struct HashTable *table, char *k) {

	int index = calculateIndex(k, table->size);
	int count = 0;
	
	while(table->arr[index].key != NULL && strcmp(table->arr[index].key, k) != 0 && count < table->size) {
		index++;
		count++;
		index %= table->size;
	}
	
	if(table->arr[index].key != NULL && strcmp(table->arr[index].key, k) == 0) {
		struct Node *tmp = (struct Node*) malloc (sizeof(struct Node));
		tmp = table->arr[index].values;
	
		return tmp;
	}
	return NULL;
}

// Searches the given prompt in the table and prints the results
void search(struct HashTable *table, char *prompt) {

	char **words = (char **) malloc (3 * sizeof(char *));
	char delim[2] = " ";
	char *ptr;
	struct Node *list1;
	struct Node *list2;
	char *originalPrompt = strdup(prompt);
	
	// Dividing the given prompt word by word
	int i = 0;
	ptr = strtok(prompt, delim);
	words[i] = strdup(ptr);
	while(ptr != NULL && i < 3) {
		i++;
		ptr = strtok(NULL, delim);
		words[i] = strdup(ptr);
	}
	
	// Invalid number of words in input
	if(i == 2 || i == 4) {
		printf("Invalid search.\n");
		for(i = 0 ; i < 3; i++) {
			printf("Word %d: %s-\n", i, words[i]);
		}
		return;
	}
		
	// Second word isn't "ve" nor "veya"
	if(i > 1 && strcmp(words[1], "ve") != 0 && strcmp(words[1], "veya") != 0) {
		printf("\"%s\" is an invalid search prompt.\n", words[1]);
		for(i = 0 ; i < 3; i++) {
			printf("Word %d: %s-\n", i, words[i]);
		}
		return;
	}
	
	
	printf("Search results for: \"%s\"\n\n", originalPrompt);
	
	// If only 1 word is searched
	if(i == 1) {
		
		list1 = findSites(table, words[0]);
		
		if(list1 == NULL) {
			printf("\t\n");
		}
		
		while(list1 != NULL) {
			printf("\t%s\n", list1->value);
			list1 = list1->next;
		}
		return;
	}
	
	/*
		The program does the following when 2 keywords are searched:
	 		Create a new hashtable
			Count how many times the websites are mentioned in searched keywords using the new hashtable 
			If at least 1 => or
			If 2 times => and
	*/
	
	struct HashTable *searchTable = (struct HashTable*) malloc (sizeof(struct HashTable));
	searchTable->size = table->count;
	searchTable->arr = (struct Key*) malloc (searchTable->size * sizeof(struct Key));
    for(i = 0; i < searchTable->size; i++) {
        searchTable->arr[i].values = NULL;
        searchTable->arr[i].key = NULL;
    }
	
	list1 = findSites(table, words[0]);
	list2 = findSites(table, words[2]);
	
	while(list1 != NULL) {
		insertTable(searchTable, list1->value, " ");
		list1 = list1->next;
	}
	
	while(list2 != NULL) {
		insertTable(searchTable, list2->value, " ");
		list2 = list2->next;
	}
	
	system("cls");
	
	printf("Search results for: \"%s\"\n\n", originalPrompt);
	
	// "and"
	if(strcmp(words[1], "ve") == 0) {
		for(i = 0; i < searchTable->size; i++) {
			if(searchTable->arr[i].values != NULL && (searchTable->arr[i].values->next != NULL)) {
				printf("\t%s\n", searchTable->arr[i].key);
			}
		}
	}
	
	// "or"
	else {
		for(i = 0; i <searchTable->size; i++) {
			if(searchTable->arr[i].values != NULL) {
				printf("\t%s\n", searchTable->arr[i].key);
			}
		}
	}
	
	
}

// Insert new website to the given list
void insertNode(struct HashTable *table, int index, char *k, char *v) {
	
	// Inserting key
	table->arr[index].key = strdup(k);
	
	// Inserting value
	struct Node *tmp = (struct Node*) malloc (sizeof(struct Node));
	tmp->next = table->arr[index].values;
	tmp->value = strdup(v);
	table->arr[index].values = tmp;
}

// Displays the whole table with additional information 
void displayTable(struct HashTable *table) {
    int i;
    struct Node *tmp;
    printf("==============\n");
    printf("Table size:%4d, Element Count: %4d\n", table->size, table->count);
    for(i = 0; i < table->size; i++) {
        printf("-----------------\n");
		printf("Index: %3d\tKey: %-10s\n\n", i, table->arr[i].key);
        tmp = table->arr[i].values;
		while(tmp != NULL) {
			printf("\t\t%s\n", tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
    }
    printf("==============\n");
}

// Calculates each key's integer value with Horner's Method 
int calculateIndex(char *key, int tableSize) {

    int i;
    int h = 0;
    int r = 1;
    int letter;
    for(i = 0; i < strlen(key); i--) {
        letter = key[i] - 'A' + 1;
        letter *= r;
        r *= 31;
        h += letter;
    }
    return h % tableSize;
}

// Inserts a new value into the hash table using Linear Probing
void insertTable(struct HashTable *table, char *k, char *v) {
    
    int index = calculateIndex(k, table->size);
    
    printf("\nCurrent table count: %d\n", table->count);
    printf("Inserting key: %s-, value: %s-, initial index calculation: %d\n", k, v, index);
   
	// Calculating index with Linear Probing
    int count = 0;
	while (table->arr[index].key != NULL && strcmp(table->arr[index].key, k) != 0 && count < table->size) {
        index++;
        count++;
        index %= table->size;
    }
    
    // If a new keyword is entered
	if(table->arr[index].values == NULL) {
        table->count++;
    }
    
    insertNode(table, index, k, v);

	printf("Updated key: %s, Updated value: %s, Updated index: %d, Took %d tries\n", table->arr[index].key, v, index, count + 1);
}

// Opens the given file and adds each key-value pair to the hash table
void readFile(char fileName[50], struct HashTable *table) {

    FILE *fp;
    fp = fopen(fileName, "r");
    char keyword[255];
    char url[255];
    char delim[2] = " ";
    char *ptr;
    
    
    if (fp == NULL) {
        printf("Couldn't open the file.\n");
    } else {
        while(!feof(fp)) {
            fscanf(fp, "%s\n", url);
            fscanf(fp, "%[^\n]\n", keyword);
			printf("Website: %s\n", url);
		    printf("Keywords: ");
            printf("%s\n", keyword);
            ptr = strtok(keyword, delim);
			while(ptr != NULL) {
                insertTable(table, ptr, url);
                ptr = strtok(NULL, delim);
            }
            printf("\n\n");
        }
    }

    fclose(fp);

}

// A function to check if the given integer is primary
int isPrimary(int n) {
    
    int i;

	if(n < 0) {
		return 0;
	}

    if(n == 0 || n == 1) {
        return 0;
    }
    if(n == 2) {
        return 1;
    }

    for(i = 2; i < (n/2); i++) {
        if((n % i) == 0) {
            return 0;
        }
    }
    
    return 1;

}

// Calculates the hash table's size with load factor
int calculateSize(int count, double lf) {
	
	int n = count * (1 / lf);
	
	int i = 0;
	
	while(1) {
		
		if(isPrimary(n + i) == 1) {
			return n + i;
		}
		
		if(isPrimary(n - i) == 1) {
			return n - i;
		}
		i++;
	}
}

int main() {

    int i, mode;
    double loadFactor;
    char fileName[50];
    
    // Getting user inputs
    printf("Filename: ");
    scanf(" %s", fileName);
    printf("Enter lf: ");
    scanf("%lf", &loadFactor);
    
    printf("Mode:\n\t0-) Normal\n\t1-)Detailed\n");
    scanf("%d", &mode);
    
    // This part is for counting unique keys
    struct HashTable *tmp = (struct HashTable*) malloc (sizeof(struct HashTable));
    tmp->arr = (struct Key*) malloc (1000 * sizeof(struct Key));
    for(i = 0; i < 1000; i++) {
        tmp->arr[i].values = NULL;
        tmp->arr[i].key = NULL;
    }
    readFile("Sample.txt", tmp);
    system("cls");
    
    // Creating the main table
    struct HashTable *table = (struct HashTable*) malloc (sizeof(struct HashTable));
	table->size = calculateSize(tmp->count, loadFactor);
	table->arr = (struct Key*) malloc (table->size * sizeof(struct Key));
    for(i = 0; i < table->size; i++) {
        table->arr[i].values = NULL;
        table->arr[i].key = NULL;
    }
	
	// Reading text file
	readFile(fileName, table);
	displayTable(table);
	if(mode == 0) {
		system("cls");
	}

	// Main program loop
	char buffer[50];
	int cont;
	
	do {
		printf("Search: ");
		scanf(" %[^\n]", buffer);
		system("cls");
		search(table, buffer);

		
		printf("\nPress '1' to continue. Anything else to exit\n\n");
        cont = getch() - '0';
        
	} while (cont == 1);
	

    return 0;
}
