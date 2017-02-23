#include <stdio.h>
#include <stdlib.h>

char buff[100];
char *nextch = buff;

struct node {
	int value;
	struct node *left;
	struct node *right;
};

struct node *create_node(struct node *left,int value,struct node *right)
{
	struct node *p=(struct node *)malloc(sizeof(struct node));
	p->value = value;
	p->left = left;
	p->right = right;
	return p;
}

/*
void print_tree(struct node *nodep)
{
	if(nodep==0){
		printf("-");
		return;
	}
	if(nodep->left || nodep->right){
		printf("<");

		if(nodep->left!=0)
			print_tree(nodep->left);
		else
			printf("-");

		printf(",%d,",nodep->value);

		if(nodep->right!=0)
			print_tree(nodep->right);
		else
			printf("-");

		printf(">");
	} else if (nodep)
		printf("%d",nodep->value);
}

void print_tree(struct node *p)
{
	if(p){
		printf("<");
		print_tree(p->left);
		printf(",%d,",p->value);
		print_tree(p->right);
		printf(">");
	} else
		printf("-");
}
*/

int print_tree(struct node *nodep)
{
	if(!nodep){
		printf("-");
		return 0;
	}

	if(!nodep->left && !nodep->right){
		printf("%d",nodep->value);
		return 1;
	}

	printf("<");
	print_tree(nodep->left);

	//if(!print_tree(nodep->left))
		//printf("-");

	printf(",%d,",nodep->value);

	print_tree(nodep->right);

	//if(!print_tree(nodep->right))
		//printf("-");

	printf(">");
	return 1;
}

void print_node(struct node *nodep)
{
	if(nodep){
		printf("node->value = %d\n",nodep->value);
	}else
		printf("node->value = 0\n");
}

void check_node(struct node *nodep)
{
	static int prev = -1;
	//print_node(nodep);
	if(nodep){
		if(nodep->value < prev){
			printf("incorrect order\n");
			//nodep->right = 0;
		}
		prev = nodep->value;
	}else
		printf("check_node; this node is 0;\n");
}

int read_number(void)
{
	int sum=0;
	while (('0' <= *nextch) && (*nextch <= '9')) {
		sum = sum*10 + (*nextch-'0');
		nextch++;
	}
	return sum;
}

int char_ok(char c)
{
	if (*nextch==c) {
		nextch++;
		return 1;
	} else {
		printf("error %c:%s\n",c, nextch);
		return 0;
	}
}

struct node *read_tree(void)
{
	int value;
	struct node *left, *right;

	if (*nextch=='-'){ // case1
		nextch++;
		return 0;
	}

	if (('0'<=*nextch) && (*nextch<='9')) // case2
		return create_node(0, read_number(), 0);

	if (!char_ok('<')) //case3
		return 0;

	left = read_tree();

	if (!char_ok(','))
		return 0;

	value = read_number();

	if (!char_ok(','))
		return 0;

	right = read_tree();

	if (!char_ok('>'))
		return 0;

	return create_node(left, value, right);
}

int search_bt(struct node *nodep, int key)
{
	print_node(nodep);

	if (!nodep)
		return 0;
	else if (nodep->value == key)
		return 1;
	else if (nodep->value > key)
		return search_bt(nodep->left,key);
	else
		return search_bt(nodep->right,key);
}

void dfs_print1(struct node *nodep)
{
	if(!nodep)
		return;

	print_node(nodep);
	dfs_print1(nodep->left);
	dfs_print1(nodep->right);
}

void dfs_print2(struct node *nodep)
{
	if(!nodep)
		return;

	dfs_print2(nodep->left);
	print_node(nodep);
	dfs_print2(nodep->right);
}

void dfs_print3(struct node *nodep)
{
	if(!nodep)
		return;

	dfs_print3(nodep->left);
	dfs_print3(nodep->right);
	print_node(nodep);
}

void check_bt(struct node *nodep)
{
	if(!nodep)
		return;

	check_bt(nodep->left);
	check_node(nodep);
	check_bt(nodep->right);
}

void insert_bt(struct node *nodep,struct node **ptr, int key)
{
	if (!nodep){
		*ptr = create_node(0,key,0);
		return;
	} else if (nodep->value == key){
		return;
	} else if (nodep->value > key){
		ptr = &(nodep->left);
		insert_bt(nodep->left,ptr,key);
	} else {
		ptr = &(nodep->right);
		insert_bt(nodep->right,ptr,key);
	}
}

int main(void)
{
	struct node *root;
	int key;

	printf(">> ");
	scanf("%s",buff);
	root = read_tree();

	printf("=> ");
	print_tree(root);
	printf("\n");

	//printf("key>> ");
	//scanf("%d",&key);
	//printf("key=> %d\n",search_bt(root,key));

	//printf("dfs_print1\n");
	//dfs_print1(root);

	//printf("dfs_print2\n");
	//dfs_print2(root);

	//printf("dfs_print3\n");
	//dfs_print3(root);

	//check_bt(root);

	/*
	print_tree(root);
	printf("\n");
	printf("key>> ");
	scanf("%d",&key);
	insert_bt(root,&root,key);
	print_tree(root);
	printf("\n");
	check_bt(root);
	*/

	return 0;
}
