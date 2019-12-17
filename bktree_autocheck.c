#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TOL 2
#define ALPHABET_SIZE 26

typedef struct node_bk{
  char* string;
  struct node_bk* children[100];
}node_bk;

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};
//BK TREE FUNCTIONS
int calculate_edit_distance(char* , char*, int , int );
node_bk* create_new_node(char*);
void add(node_bk*, char*);
int min(int, int, int);
//TRIE TREE FUNCTIONS
int CHAR_TO_INDEX(char c);
int search(struct TrieNode *root, const char *key);
int isLeafNode(struct TrieNode* root);
void display(struct TrieNode* root, char str[], int level);
struct TrieNode *getNode(void);
void form_trietree(char* filename, struct TrieNode *root);
//HELPER FUNCTIONS
void make_lower(char*);

/************************************ALL THE FUNCTIONS RELATED TO THE BK TREE ***********************************/
void make_lower(char* string){
  for(int i=0;i<strlen(string);i++){
    if(isupper(string[i]))
      string[i] = tolower(string[i]);
  }
}
node_bk* create_new_node(char* word){
  node_bk* new_node = (node_bk*)malloc(sizeof(node_bk));
  new_node->string = (char*)malloc(sizeof(char)*50);
  strcpy(new_node->string, word);
  for(int i=0;i<100;i++){
    new_node->children[i] = NULL;
  }
}

void add(node_bk* root, char* curr){
    int distance = calculate_edit_distance(curr, root->string, strlen(curr), strlen(root->string));

    if(root->children[distance]==NULL)
      root->children[distance] = create_new_node(curr);
    else
      add(root->children[distance],curr);
}

void printSimilarWords(node_bk* root, char* target){
  if(root==NULL){
    return ;
  }
  int distance = calculate_edit_distance(root->string,target, strlen(root->string)-1, strlen(target));

  if(distance<=TOL)
    printf("%s\n", root->string);

  int start = distance-TOL;

  if(start<0)
    start = 0;

  while(start < distance + TOL){
    printSimilarWords(root->children[start],target);
    start+=1;
  }
}

int min(int a, int b, int c){
  int temp = (a < b)? a : b;
  int min =  (c < temp)? c : temp;
  return min;
}


void form_bktree(node_bk* root, char* filename){
  FILE * fp = fopen(filename, "r");
  if (fp == NULL) return ;
  char c;
  int end = 0;
  char string_to_add[60];
  int i;
  while((c = fgetc(fp)) != EOF){
    i = 0;
    while(c!= ' ' && c!= '\n'){
      string_to_add[i] = c;
      c = fgetc(fp);
      if(c==EOF){
        end=1;
        i+=1;
        break;
      }
      i += 1;
    }
    string_to_add[i] = '\0';
    make_lower(string_to_add);
    add(root, string_to_add);
    if(end)
      break;
  }
  fclose(fp);
}

int calculate_edit_distance(char* string1, char* string2, int m, int n){
  // Create a table to store results of subproblems
    int dp[m+1][n+1];
    for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++){
            if (i==0)
                dp[i][j] = j;
            else if (j==0)
                dp[i][j] = i;
            else if (string1[i-1] == string2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]); // Replace
        }
    }
    return dp[m][n];
}

/****************************ALL THE DATA STRUCTURES AND FUNCTIONS RELATED TO THE TRIE TREE******************/

int CHAR_TO_INDEX(char c){
	return ((int)c - (int)'a');
}

//Seaches for a string key in the trie tree with root as *root
int search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++){
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

//Checks if a particular node is the leaf node by checking for the isEndOfWord bit
int isLeafNode(struct TrieNode* root){
    if(root->isEndOfWord){
    	return 1;
    }
    return 0;
}

//A recursive function to display the contents of the trie
void display(struct TrieNode* root, char str[], int level){
    if (isLeafNode(root)){
        str[level] = '\0';
        printf("%s\n",str);
    }

    int i;
    for (i = 0; i < 26; i++){
        if (root->children[i]){
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void){
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode){
        int i;

        pNode->isEndOfWord = 0;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}


void form_trietree(char* filename, struct TrieNode *root){
		FILE * fp = fopen(filename, "r");
		if (fp == NULL) return ;
		char c;
		int end=0;
		int count = 0;
		int index;
		while((c = fgetc(fp)) != EOF){
			struct TrieNode *pCrawl = root;
			while(c!= ' ' && c!= '\n'){
				if(isupper(c))
					c = tolower(c);
				index = CHAR_TO_INDEX(c);
				if(index<0){
					break;
				}
				if(!pCrawl->children[index])
					pCrawl->children[index] = getNode();

				pCrawl = pCrawl->children[index];
				c = fgetc(fp);
				if(c==EOF){
					end=1;
					break;
				}
			}
			pCrawl->isEndOfWord = 1;
			if(end)
				break;
		}
		fclose(fp);
}

/****************************START OF THE MAIN FUNCTION*********************************/
int main(){
  char input[60];
  int n;
  int i = 0;
  node_bk* root_node = create_new_node("abandonable");
  struct TrieNode *root = getNode();
  printf("Forming Trie Tree.....\n");
  form_trietree("dict_trie.txt",root);
  printf("Forming BK Tree.....\n");
  form_bktree(root_node, "dict_bk.txt");
  printf("Please enter the number of input words: ");
  scanf("%d",&n);
  while(i<n){
    printf("Please give in the input word: ");
    scanf("%s",input);
    make_lower(input);
    if(!search(root, input)){
      printf("The given input word in wrong and the suggestions are as follows:\n");
      printSimilarWords(root_node, input);
    }
    else{
      printf("The given input word in correct, as it is present in the dictionary.\n");
    }
    i = i + 1;
  }
  return 0;
}
