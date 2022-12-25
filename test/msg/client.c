#include <fcntl.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>




int main(void)
{
#if 0

       key_t ftok(const char *pathname, int proj_id);
#endif
	struct msgbuf1 {
		long mtype;       /* message type, must be > 0 */
		char mtext[10];    /* message data */
	};

	struct msgbuf1 buff = {};
	key_t key;
	int msgid;
	key = ftok("ftok.file", 'A');
#if 0
             S_IRUSR  00400 user has read permission

              S_IWUSR  00200 user has write permission
#endif
	msgid = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
	fprintf(stdout, "msgid :%d\n", msgid);
#if 0
       int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
                      int msgflg);
#endif
	fprintf(stdout, "mtext:%s\n", buff.mtext);
	msgrcv(msgid, &buff, sizeof(buff), 1, 0);
	fprintf(stdout, "mtext:%s\n", buff.mtext);

	return 0;
}
