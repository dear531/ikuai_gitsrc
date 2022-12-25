#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{
#if 0

       key_t ftok(const char *pathname, int proj_id);
#endif
	struct msgbuf1 {
		long mtype;       /* message type, must be > 0 */
		char mtext[10];    /* message data */
	};

	struct msgbuf1 buff = {.mtype = 1, .mtext = "a",};
	key_t key;
	int msgid;
#if 0
int creat(const char *pathname, mode_t mode);
#endif
	creat("ftok.file", O_CREAT | S_IRUSR | S_IWUSR);
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
	msgsnd(msgid, &buff, sizeof(buff), 0);
	return 0;
}
