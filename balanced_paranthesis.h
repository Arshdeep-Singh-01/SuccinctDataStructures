#pragma once
# include "definitions.h"

extern node* bp;

void balanced_paranthesis(tree ** k);
void Balanced_Paranthesis(tree ** k,int n);
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