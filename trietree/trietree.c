/*
 * 代码仍有诸多不完善，比如当一个节点删除之后，只删除了末端节点，而除了末端之上的其他节点都残留在了数据中
 * 而搜索的时候，无法确定从开始匹配，但要查找的字符串全都比较完，但存储路径未结束时的比较，是否是存入的节点，还是因为有更长的数据插入
 * 写代码时，只是为了实现数据结构，尝试性编程
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 26

struct node {
	struct node * next;
};

int search_trie_tree(struct node *root, char *word)
{
	int i = 0;
	struct node *curr = root;
	for (i = 0; i < 100 && word[i] != 0; i++) {
		if (NULL == curr[word[i] - 'a'].next) {
			return -1;
		} else {
			curr = curr[word[i] - 'a'].next;
		}
	}

	return 0;
}

int insert_trie_tree(struct node *root, char *word)
{
	int i = 0;
	struct node *curr = root;
	for (i = 0; i < 100 && word[i] != 0; i++) {
		if (NULL == curr[word[i] - 'a'].next) {
			curr[word[i] - 'a'].next = malloc(sizeof(*curr[word[i] - 'a'].next) * NUMBER);
			curr = curr[word[i] - 'a'].next;
		}
	}
	return 0;
}

int delete_trie_tree(struct node *root, char *word)
{
	int i = 0, recode_i = 0;
	struct node *curr = root, *prov = NULL;
	for (i = 0; i < 100 && word[i] != 0; i++) {
		if (NULL != curr[word[i] - 'a'].next) {
			prov = curr;
			recode_i = i;
			curr = curr[word[i] - 'a'].next;
		} else {
			return -1;
		}
	}
	fprintf(stdout, "%c\n", word[recode_i]);
	free(prov[word[recode_i] - 'a'].next);
	prov[word[recode_i] - 'a'].next = NULL;
	return 0;
}

int main(void)
{
	struct node *root = NULL;
	root = malloc(sizeof(*root) * NUMBER);
	memset(root, 0x00, sizeof(root) * NUMBER);
	char str[100 + 1] = {0};
	while (1) {
		memset(str, 0x00, sizeof(str));
		scanf("%s", str);
		if (0 == memcmp("1", str, strlen("1"))) {
			fprintf(stdout, "insert :\n");
			memset(str, 0x00, sizeof(str));
			scanf("%s", str);
			insert_trie_tree(root, str);
		} else if (0 == memcmp("2", str, strlen("1"))) {
			fprintf(stdout, "search :\n");
			memset(str, 0x00, sizeof(str));
			scanf("%s", str);
			if (0 == search_trie_tree(root, str)) {
				fprintf(stdout, "str :%s is exists\n", str);
			} else {
				fprintf(stdout, "str :%s is not exists\n", str);
			}
		} else if (0 == memcmp("3", str, strlen("1"))) {
			fprintf(stdout, "delete :\n");
			memset(str, 0x00, sizeof(str));
			scanf("%s", str);
			delete_trie_tree(root, str);
		} else if (0 == memcmp("4", str, strlen("1"))) {
			break;
		}
	}
	return 0;
}
