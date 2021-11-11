# include <stdio.h>
# include <stdlib.h>


struct Tree{
    int data;
    int number_of_children;
    struct Tree** children; 
}typedef tree;


struct Node{
    int posn;
    char pr;
}typedef node;

int count=0;
int number_of_nodes=0;
node* bp=NULL;

void addNode(tree ** k);
void display(tree** r);
void balanced_paranthesis(tree ** k);
void display_bp(void);
int find_close(int i);
int find_open(int i);
int enclose(int i);


int rank(char type,int i);
int select(char type, int i);
int parent(int v);
int firstchild(int v);
int sibling(int v);
int lastchild(int v);
int depth(int v);
int subtreesize(int v);
int degree(int v);

int main(){
    tree * root=NULL;
    addNode(&root);
    display(&root);
    bp=(node*)malloc(2*sizeof(node)*number_of_nodes);
    balanced_paranthesis(&root);
    display_bp();

    printf("parent of %d : %d\n",bp[4].posn,parent(4));
    printf("first child of %d : ", bp[4].posn);
    if (firstchild(4) != -1) {
        printf("%d\n",firstchild(4));
    }
    printf("last child of %d : ", bp[4].posn);
    if (lastchild(4) != -1) {
        printf("%d\n", lastchild(4));
    }
    printf("sibling of %d : %d\n",bp[4].posn,sibling(4));
    printf("depth %d : %d\n",bp[4].posn,depth(4));
    printf("subtree size of %d : %d\n",bp[4].posn,subtreesize(4));

    return 0;
}

void addNode(tree ** k){
    *k=(tree *)malloc(sizeof(tree));
    int d,t;
    printf("Enter data of node: ");
    scanf("%d",&d);
    (*k)->data=d;
    number_of_nodes++;
    printf("Enter number of children: ");
    scanf("%d",&t);
    if(t>0) (*k)->children =(tree**)malloc(t*(sizeof(tree*)));
    (*k)->number_of_children=t;
    for(int i=0;i<t;i++){
        printf("\nAdd child %d of node %d:\n",i+1,(*k)->data);
        addNode(&((*k)->children[i]));
    }  
}

void display(tree** r){
    printf("%d ",(*r)->data); 
    for(int i=0;i<(*r)->number_of_children;i++){
        display(&((*r)->children[i]));
    }
    printf("\n");  
}

void display_bp(void){
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%c ",bp[i].pr);
    }
    printf("\n");
    for(int i=0;i<2*number_of_nodes;i++){
        printf("%d ",bp[i].posn);
    }
    printf("\n");
}

void balanced_paranthesis(tree ** r){
    bp[count].posn=(*r)->data;
    bp[count].pr='(';
    count++;
    for(int i=0;i<(*r)->number_of_children;i++){
        balanced_paranthesis(&((*r)->children[i]));
    }
    bp[count].posn=(*r)->data;
    bp[count].pr=')';
    count++;
}

int find_close(int i)
{
    int temp = bp[i].posn;
    for(int j=i+1; j<2*number_of_nodes; j++)
    {
        if(bp[j].posn == temp)
        {
            return j;
        }
        
    }
}

int find_open(int i){
    int temp = bp[i].posn;
    for(int j=i-1; j>-1; j--)
    {
        if(bp[j].posn == temp)
        {
            return j;
        }
    }
}

int enclose(int i){
    int count = 0;
    for(int j = i - 1; j > -1 ; j--){
        if(bp[j].pr == '('){
            count++;
        }
        else{
            count--;
        }
        if(count>0){
            return j;
        }
    }
}

int rank(char type,int i){
    int count =0;
    for(int j = i; j >-1 ; j--){
        if(bp[j].pr == type){
            count++;
        }
    }
    return count;
}

int select(char type, int i){
    int j;
    for(j = 0; j < 2*number_of_nodes && i>0 ; j++){
        if(bp[j].pr == type){
            i--;
        }
    }
    return j;
}

int parent(int v){
    return bp[enclose(v)].posn;
}


int firstchild(int v){
    if (bp[v].pr == '(') {
        if (find_close(v) == v+1) {

            printf("NULL\n");
            return -1;
        }
        else {
            return bp[v + 1].posn;
        }
    }
    if (bp[v].pr == ')') {
        firstchild(find_open(v));
    }
}

int sibling(int v){
    return bp[find_close(v) + 1].posn;
}

int lastchild(int v){
    if (bp[v].pr == ')') {
        if (find_open(v) == v - 1) {
            printf("NULL\n");
            return -1;
        }
        else {
            return bp[find_open(v - 1)].posn;
        }
    }
    else {
        lastchild(find_close(v));
    }
}

int depth(int v){
    return bp[rank('(', v) - rank(')', v)].posn;
}

int subtreesize(int v){
    return bp[(find_close(v) - v + 1) / 2].posn;
}