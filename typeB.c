#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void print_tree(struct node *nodep)
{
	/* case1 */
	if(!nodep){
		printf("-");
		return;
	}

	/* case2 */
	if(!nodep->left && !nodep->right){
		printf("%d",nodep->value);
		return;
	}

	/* case3 */
	printf("<");
	print_tree(nodep->left);
	printf(",%d,",nodep->value);
	print_tree(nodep->right);
	printf(">");
}
void print_node(struct node *nodep)
{
	if(nodep)
		printf("node->value = %d\n",nodep->value);
	else
		printf("node->value = 0\n");
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

	/* case1 */
	if (*nextch=='-'){
		nextch++;
		return 0;
	}

	/* case2 */
	if (('0'<=*nextch) && (*nextch<='9'))
		return create_node(0, read_number(), 0);

	/* case3 */
	if (!char_ok('<'))
		return 0;

	left = read_tree(); // left

	if (!char_ok(','))
		return 0;

	value = read_number(); // value

	if (!char_ok(','))
		return 0;

	right = read_tree(); // right

	if (!char_ok('>'))
		return 0;

	return create_node(left, value, right);
}

int search_bt(struct node *nodep, int key)
{
	//print_node(nodep);

	if (!nodep)
		return 0;

	else if (nodep->value == key)
		return 1;

	else if (nodep->value > key)
		return search_bt(nodep->left,key);

	else
		return search_bt(nodep->right,key);
}

int prev = -1;
int check_node(struct node *nodep)
{
	//print_node(nodep);

	if(!nodep){
		printf("check_node; this node is 0;\n");
		return 0;
	}

	if(nodep->value < prev){
		printf("incorrect order\n");
		prev = -1;
		return 0;
	}
	prev = nodep->value;

	return 1;
}
int check_bt(struct node *nodep)
{
	if(!nodep)
		return -1;

	if(!check_bt(nodep->left))
		return 0;

	if(!check_node(nodep))
		return 0;

	if(!check_bt(nodep->right))
		return 0;

	return 1;
}
void check(struct node *nodep){
	if(check_bt(nodep)==1)
		printf("this Btree is OK.\n");
	prev=-1;
}

int insert_bt(struct node *nodep,struct node **ptr, int key)
{
	int ret = 0;
	if (!nodep){
		*ptr = create_node(0,key,0);
		return -1;

	} else if (nodep->value == key)
		return 0;

	else if (nodep->value > key){
		ret = insert_bt(nodep->left,&(nodep->left),key);
		if(!ret)
			return 0;
		else if(ret==-1)
			return 1;
		else
			return ret+1;
	}else{
		ret = insert_bt(nodep->right,&(nodep->right),key);
		if(!ret)
			return 0;
		else if (ret==-1)
			return 1;
		else
			return ret+1;
	}
}

int main(void)
{
	struct node *root;
	int key,r,depth,i;

	srand(time(0));
	printf(">> ");
	scanf("%s",buff);
	root = read_tree();
	/*
	printf("=> ");
	print_tree(root);
	printf("\n");
	printf("key>> ");
	scanf("%d",&key);
	printf("key=> %d\n",search_bt(root,key));
	*/
	check(root);
	/*
	print_tree(root);
	printf("\n");
	printf("key>> ");
	scanf("%d",&key);
	printf("ret = %d\n",insert_bt(root,&root,key,0));
	print_tree(root);
	printf("\n");
	check_bt(root);
	*/
	for(i=0; i<10; i++) {
		r=rand()%100;
		depth=insert_bt(root,&root,r);
		printf("key=%d, depth=%d\n",r,depth);
		print_tree(root);
		printf("\n");
		check(root);
		printf("\n");
	}
	return 0;
}
