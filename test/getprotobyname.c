#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
#if 0
           struct protoent {
               char  *p_name;       /* official protocol name */
               char **p_aliases;    /* alias list */
               int    p_proto;      /* protocol number */
           }
#endif
	struct protoent * ent = NULL;
	int i = 0;
	if (2 != argc) {
		fprintf(stderr, "usage: %s <protocolname>\n", argv[0]);
		fprintf(stderr, "usage: %s tcp\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	ent = getprotobyname(argv[1]);

	fprintf(stdout, "p_name:%s, p_proto:%d\n",
              ent->p_name, ent->p_proto);
	for (i = 0; NULL != ent->p_aliases[i]; i++) {
		fprintf(stdout, "p_aliases[%d]:%s\n",
			i, ent->p_aliases[i]);
	}
	return 0;
 
 
 
}
