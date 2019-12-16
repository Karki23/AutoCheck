#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOL 2

typedef struct node_bk{
  char* string;
  struct node_bk* children[100];
}node_bk;

int calculate_edit_distance(char* , char*, int , int );
node_bk* create_new_node(char*);
void add(node_bk*, char*);
int min(int, int, int);

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
  int distance = calculate_edit_distance(root->string,target, strlen(root->string), strlen(target));

  if(distance<=TOL)
    printf("%s\n", root->string);

  int start = distance-TOL;

  if(start<0)
    start = 1;

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

int main(){
  node_bk* root_node = create_new_node("help");
  add(root_node, "hello");
  add(root_node, "hell");
  add(root_node, "loop");
  add(root_node, "helps");
  add(root_node, "shell");
  add(root_node, "helper");
  add(root_node, "troop");
  printSimilarWords(root_node, "oop");
  return 0;
}
