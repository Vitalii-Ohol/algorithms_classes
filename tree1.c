#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
	char data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};

struct Node* newNode() {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = ' ';
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

void insert(struct Node* root, char* str, unsigned int index) {
	struct Node* tmp = root;
	if(index >= strlen(str)-1)
	{
		tmp->data = str[0];
		return;
	}
	unsigned int i;
	for(i=index; i<strlen(str)-1; i++){
		if(str[i] == 'L')
		{
			if(tmp->left == NULL) tmp->left = newNode();
			tmp->left->parent = tmp;
			tmp = tmp->left;
		} else {
			if(tmp->right == NULL) tmp->right = newNode();
			tmp->right->parent = tmp;
			tmp = tmp->right;
		}
	}
	tmp->data = str[0];
	return;
}

void print(struct Node* root, char** string){
	if(root == NULL) return;
	if(root->left != NULL) print(root->left, string);
	if(root->right!= NULL) print(root->right, string);
	if(root->left == NULL && root->right == NULL)
	{
		struct Node* maxnode = root;
		char* tmp = (char*)malloc(20);
		tmp[0] = '\0';
		while(maxnode != NULL)
		{
			size_t len = strlen(tmp);
			char* st = (char*)malloc(len+2);
			strcpy(st, tmp);
			free(tmp);
			st[len] = (char)maxnode->data;
			st[len+1] = '\0';
			tmp = st;
			maxnode = maxnode->parent;
		}
		if(strcmp(*string, tmp)<0){
			free(*string);
			*string = tmp;
		}
	}
}

void postOrderFree(struct Node* root){
	if(root != NULL) {
		postOrderFree(root->left);
		postOrderFree(root->right);
		free(root);
	}
}

int main() {
	int count = 0;
	char buf[BUFSIZ];
	struct Node *root = newNode();
	char* t = (char*)malloc(20);
	while(fgets(buf, sizeof(buf), stdin) != NULL){
		size_t m;
		for(m=0; m<strlen(buf)-1; m++)
			if(((int)buf[m] > 96 && (int)buf[m] < 123) || ((int)buf[m] > 66 && (int)buf[m] < 91)) 
				count++;
		insert(root, buf, 2);
	}
	print(root, &t);
	fprintf(stdout, "%s\n%d", t, count);
	postOrderFree(root);
	free(t);
	return 0;
}
