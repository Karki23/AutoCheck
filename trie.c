#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
// This function calculates the index of the trie tree where a particular node must be inserted
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

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

//Checks if a particular node is the leaf node by checking for the isEndOfWord bit
int isLeafNode(struct TrieNode* root)
{
    if(root->isEndOfWord){
    	return 1;
    }
    return 0;
}

//A recursive function to display the contents of the trie
void display(struct TrieNode* root, char str[], int level)
{
    if (isLeafNode(root))
    {
        str[level] = '\0';
        printf("%s\n",str);
    }

    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = 0;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}


void form_trie_tree(char* filename, struct TrieNode *root)
{
		FILE * fp = fopen(filename, "r");
		if (fp == NULL) return ;
		char c;
		int end=0;
		int count = 0;
		int index;
		while((c = fgetc(fp)) != EOF)
		{
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
