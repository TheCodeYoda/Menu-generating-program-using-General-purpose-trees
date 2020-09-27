#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

struct node
{
	char *key;
	struct node* left;
	struct node* right;
};
typedef struct node node_t;

struct tree
{
	node_t *root;
};
typedef struct tree tree_t;

// code generating functions....

void gen_fn(const char* fname)
{
	printf("void fxn_%s()\n", fname);
	printf("{\n");
	printf("	printf(\"%s\\n\");\n", fname);
	printf("}\n");
}

void gen_header()
{
	printf("#include <stdio.h>\n");

}

void prolog()
{
	printf("int main()\n");
	printf("{\n");
	
}

void epilog()
{

	printf("}\n");
	
}

void gen_while()
{
	printf("	int opt;\n");
	printf("	scanf(\"%%d\", &opt);\n");
	printf("	while(opt)\n");
	printf("	{\n");
	printf("		switch(opt)\n");
	printf("		{\n");
}

void gen_while_withoutopt()
{
	//printf("	int opt;\n");
	printf("	scanf(\"%%d\", &opt);\n");
	printf("	while(opt)\n");
	printf("	{\n");
	printf("		switch(opt)\n");
	printf("		{\n");
}

void close_while()
{
	printf("		}\n"); // close switch
	printf("		scanf(\"%%d\", &opt);\n");
	printf("	}\n"); // close while
}

void gen_case(int i, const char* s)
{
	printf("			case %d : \n", i);
	printf("				fxn_%s();\n", s);
}
void gen_break() {
	printf("				break;\n");
}

//-------------------------------------------------------------------------------

//initializes tree
void init_tree(tree_t *ptr_tree)
{
	ptr_tree->root=NULL;
}

//search the tree for a node with given key
node_t* search(node_t *t,char *key) {
	if(t!=NULL && !strcmp(t->key,key)) {
		//printf("FOUND!");
		return t;
	}
	if(t==NULL)
		return NULL;
	node_t * tmp=search(t->left,key);
	if(tmp) return tmp;
	node_t * tmp1=search(t->right,key);
	if(tmp1) return tmp1;
}

//dfs applied to generate all functions which prints contents of nodes
void disp_r_fxn(const node_t *root)
{
	gen_fn(root->key);
	if(root->left!=NULL)
		disp_r_fxn(root->left);
	if(root->right!=NULL)
		disp_r_fxn(root->right);
}
//dfs to generate the menu
void disp_r_dfs(const node_t *root, int count)
{
	gen_case(count,root->key);
	if(root->left!=NULL) {
		gen_while_withoutopt();
		disp_r_dfs(root->left,1);
		gen_break();
		close_while();
	}
	if(root->right!=NULL) {
		gen_break();
		disp_r_dfs(root->right,count+1);
		//close_while();
	}
}

//to call the recursive dfs calls to generate menu
void disp_tree(const tree_t *ptr_tree)
{
	node_t *temp=ptr_tree->root;
	if(temp==NULL) printf("NULL!!");
	gen_header();
	disp_r_fxn(temp);
	prolog();
	gen_while();
	disp_r_dfs(temp,1);
	gen_break();
	close_while();
	epilog();
}

// to add the node into the tree
void add_node(tree_t *ptr_tree, char *parent,char *node)
{	
	//printf("%s %s\n",parent,node);
	if(ptr_tree->root==NULL) {
		node_t *temp=malloc(sizeof(node_t));
		temp->key=node;
		temp->left=NULL;
		temp->right=NULL;
		ptr_tree->root=temp;
	}
	//printf("%c\n",inp[0]);
	else if(parent==" ") {
		node_t *temp=malloc(sizeof(node_t));
		temp->key=node;
		temp->left=NULL;
		temp->right=NULL;
		node_t *temp1=ptr_tree->root;
		while(temp1->right!=NULL)
			temp1=temp1->right;
		temp1->right=temp;
	}
	else if(parent!=" "){
		node_t *temp=malloc(sizeof(node_t));
		temp->key=node;
		temp->left=NULL;
		temp->right=NULL;
		node_t *par_node=search(ptr_tree->root,parent);
		if(par_node->left==NULL)
			par_node->left=temp;
		else {
			par_node=par_node->left;
			while(par_node->right!=NULL)
				par_node=par_node->right;
			par_node->right=temp;
		}
		
	}
		
}

//input function to take any size string and return it
char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    if(len==0) return NULL;
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

//classic push operation into the stack
void push(char **stack,int *top,char *x) {
	*top=*top+1;
	stack[*top]=x;
}

//like a multi pop operation pop k elements
int pop(char **stack,int *top,int k) {
	*top=*top-k;
	if(*top<=-1) {
		*top=-1;
		return 0;
	}
	return 1;
}

//trims the string
void remove_Tabs(char *str) 
{ 
    int count = 0;  
    for (int i = 0; str[i]; i++) 
        if (str[i] != '\t') 
            str[count++] = str[i];
    str[count] = '\0'; 
} 

int main()
{
	tree_t t;
	//assert(check_root(&t));
	init_tree(&t);
	//assert(check_root(&t));
	char *stack[1500];
	int top=-1;
	int prev_tab=-1;
	while(1)
	{
		int tab=0;
		char *parent;
		char *node = inputString(stdin, 10);
		if(node==NULL)
			break;
		for(int i=0;node[i]!='\0';i++) {
			if(node[i]=='\t') ++tab;
		}
		remove_Tabs(node);
		int diff=prev_tab-tab;
		if(prev_tab==-1) {
			parent=" ";
			push(stack,&top,node);
		}
		else if(diff<0) {
			parent=stack[top];
			push(stack,&top,node);
		}
		else if(diff>0) {
			if(pop(stack,&top,diff+1))
				parent=stack[top];
			else
				parent=" ";
			push(stack,&top,node);
		}
		else {
			pop(stack,&top,1);
			push(stack,&top,node);
		}
		//printf("parent : %s %d\n",parent,diff);
		prev_tab=tab;
		add_node(&t,parent,node);
		//free(node);

	}
	/*printf("root: %c\n",t.root->key);
	printf("root->left %c\n",t.root->left->key);
	printf("root->left->right %c\n",t.root->left->right->key);
	printf("root->left->right->right %c\n",t.root->left->right->right->key);	
	printf("root->left->left %c\n",t.root->left->left->key);
	printf("root->left->left->right %c\n",t.root->left->left->right->key);
	printf("root: %s\n",t.root->key);
	printf("root->right %s\n",t.root->right->key);
	printf("root->right->right %s\n",t.root->right->right->key);
	printf("root->right->right->right %s\n",t.root->right->right->right->key);*/
	//printf("root->left %s\n",t.root->left->key);
	//printf("root->left->right %s\n",t.root->left->right->key);
	//printf("root->left->right->left %s\n",t.root->left->right->left->key);
	disp_tree(&t);

}