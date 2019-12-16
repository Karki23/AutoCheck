#define ALPHABET_SIZE 26

//the trie data strcuture
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

int isLeafNode(struct TrieNode* root); //checks if a particular node in the trie tree is the leaf node, i.e, if we land at that node would we have formed a legal word?
int search(struct TrieNode *root, const char *key); //searches for a string key in the trie root
void frw(char* filename, int flag,struct TrieNode *root); // main function, flag=0 inserts the words of filename.txt into root.
														  // While flag =1 checks the spelling of the words in filename.txt and outputs a output.txt with all wrong spelling
struct TrieNode *getNode(void); //creates a new trie node by initializing all the 26 children to NULL
int CHAR_TO_INDEX(char c); // converts a given character to it's respective index in the trie data structure
void display(struct TrieNode* root, char str[], int level) ; //displays all the words in the trie tree
