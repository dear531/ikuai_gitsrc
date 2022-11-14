#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *reserved(struct node *head)
{
	struct node *pp = NULL, *p = NULL, *c = NULL, *n = head;
	if (NULL == head) {
		return head;
	}
#if 1
	do {
		p = c;
		c = n;
		n = n->next;
		c->next = p;
	} while (NULL != n);
	return c;
#endif
}

struct node *add_link(struct node *head, int data)
{
	struct node *node = malloc(sizeof(*head));
	node->data = data;
	node->next = head;
	return node;
}

void print_link(struct node *head)
{
	struct node *tmp = head;
	for (tmp = head; tmp; tmp = tmp->next) {
		printf("%d\n", tmp->data);
	}
	return;
}

struct node *init_link(int num)
{
	int i = 0;
	struct node *head = NULL;
#if 1
	for (i = 0; i < num; i++) {
		head = add_link(head, i);
	}
#endif
	return head;
}

void destroy_link(struct node *head)
{
	if (NULL == head) {
		return;
	}
	struct node *c = NULL, *n = head;
	do {
		c = n;
		n = n->next;
#if 0
		fprintf(stdout, "free c->data:%d\n", c->data);
#endif
		free(c);
	} while (NULL != n);
}

int main(void)
{
	struct node *head = NULL;
	head = init_link(4);
	print_link(head);
#if 1
	printf("====\n");
	head = reserved(head);
	print_link(head);
#endif
	destroy_link(head);
	return 0;
}
