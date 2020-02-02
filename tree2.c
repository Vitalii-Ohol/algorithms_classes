#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//#define DEBUG
//#define PRINTT

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
};


struct Node* newNode() {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->left = NULL;
	node->data = 0;
	node->right = NULL;
	node->parent = NULL;
	return node;
}


void readI(struct Node* root, uint_fast16_t* len) {
	register int single;
	register int character;
	struct Node* tmp = root;

	character = getc_unlocked(stdin);
	#ifdef DEBUG
		fprintf(stdout, "first char: %c\n", (char)character);
	#endif // DEBUG
	++(*len);

	single = getc_unlocked(stdin);
	while(single != EOF) {
		if(single == 10) {
			#ifdef DEBUG
				fprintf(stdout, "read: \\n     ");
			#endif // DEBUG
			tmp->data = character;
			tmp = root;
			character = getc_unlocked(stdin);
			if(character == -1) break;
			++(*len);
			#ifdef DEBUG
				fprintf(stdout, "new char: %d     ", character);
			#endif // DEBUG
		} else if(single == 76) {
			#ifdef DEBUG
				fprintf(stdout, "use L     ");
			#endif // DEBUG
			++(*len);
			if(tmp->left == NULL) tmp->left = newNode();
			tmp->left->parent = tmp;
			tmp = tmp->left;
		} else if(single == 82) {
			#ifdef DEBUG
				fprintf(stdout, "use R     ");
			#endif // DEBUG
			++(*len);
			if(tmp->right == NULL) tmp->right = newNode();
			tmp->right->parent = tmp;
			tmp = tmp->right;
		} else {
			#ifdef DEBUG
				fprintf(stdout, "skip     ");
			#endif // DEBUG
		}
		#ifdef DEBUG
			fprintf(stdout, "len: %u\n", *len);
		#endif // DEBUG
		single = getc_unlocked(stdin);
	}
}


void searchNode(struct Node* root, struct Node** max) {
	if(root == NULL) return;
	if(root->left != NULL) searchNode(root->left, max);
	if(root->right!= NULL) searchNode(root->right, max);
	if(root->left == NULL && root->right == NULL) {
		struct Node* first = root;
		struct Node* second = (*max);
		while(first->data == second->data) {
			first = first->parent;
			second = second->parent;
		}
		if(first->data > second->data) {
			#ifdef DEBUG
				fprintf(stdout, "root->data: %d\nmax->data: %d\n", root->data, (*max)->data);
			#endif // DEBUG
			*max = root;
		}
	}
}


#ifdef PRINTT
void print2DUtil(struct Node *root, int space) {
	if (root == NULL) return;
	space += 10;
	print2DUtil(root->right, space);
	printf("\n");
	int i;
	for (i = 10; i < space; i++) printf(" ");
	printf("%c\n", root->data);
	print2DUtil(root->left, space);
}
#endif // PRINTT


void postOrderFree(struct Node* root) {
	if(root != NULL) {
		postOrderFree(root->left);
		postOrderFree(root->right);
		free(root);
	}
}


int main() {
	uint_fast16_t length = 0;
	struct Node *root = newNode();
	struct Node* max = newNode();
	readI(root, &length);
	#ifdef DEBUG
		fprintf(stdout, "\n");
	#endif // DEBUG
	searchNode(root, &max);
	while(max != NULL) {
		putc_unlocked(max->data, stdout);
		max = max->parent;
	}
	#ifdef PRINTT
		print2DUtil(root, 0);
	#endif // PRINTT
	fprintf(stdout, "\n%u", length);
	//postOrderFree(root);
	return 0;
}
