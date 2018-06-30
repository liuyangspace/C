#include <stdio.h>
#include <string.h>
#define MAXWORD 100

struct tnode {            /* the tree node: */
    char word[MAXWORD];           /* points to the text */
    int count;            /* number of occurrences */
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
} typedef tnode;

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
tnode *newNode();
int listIndex=0;
tnode list[100];

/* word frequency count */
main()   {
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF){
        root = addtree(root, word);
    }
    treeprint(root);
    return 0;
}

int getword(char *s, int max){
    int j;
    for (j=0;j<MAXWORD;j++){
        s[j]='\0';
    }
    int i=0;
    int word=0;
    int start = 0;
    while(word=getchar()){
        if(word==EOF){
            return EOF;
        }
        if(word!=' ' && word!=',' && word!='.' && word!='\t' && word!='\n' && word!=';'){
            start=1;
            s[i++]=(char)word;
        } else if(start && (word==' ' || word==',' || word=='.' || word=='\t' || word=='\n' || word==';')){
            s[i]='\0';
            return i;
        }
    }
}

tnode *newNode(){
    return &(list[listIndex++]);
}

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)   {
    int cond;
    if (p == NULL) {
        p = newNode();
        //p->word = *w;
        strcpy(p->word,w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0){
        p->count++;
    } else if (cond < 0){
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint(tnode *root){
    int i=0;
    for(i;i<(sizeof list )/sizeof(tnode);i++){
        if(list[i].word && list[i].count){
            printf("%s\t%d\n",list[i].word,list[i].count);
        }
    }
}




