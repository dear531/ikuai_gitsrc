#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#if 0

1.
Thread 0x7fa025ce2740 (LWP 172457) "a.out"  <=> syscall(SYS_gettid)

2.
$ pstree -p |grep 16730
           |-sshd(1326)-+-sshd(52101)---sshd(52220)---bash(52221)-+-a.out(167303)-+-{a.out}(167304)
           |            |                                         |               `-{a.out}(167305)


(gdb) print tid
$2 = 172458
(gdb) info threads 
  Id   Target Id                                  Frame 
  1    Thread 0x7fa025ce2740 (LWP 172457) "a.out" __pthread_clockjoin_ex (threadid=140325805758208, thread_return=0x0, clockid=<optimized out>, 
    abstime=<optimized out>, block=<optimized out>) at pthread_join_common.c:145
* 2    Thread 0x7fa025ce1700 (LWP 172458) "a.out" 0x00007fa025dc223f in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, 
    req=req@entry=0x7fa025ce0e90, rem=rem@entry=0x7fa025ce0e90) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
  3    Thread 0x7fa0254e0700 (LWP 172459) "a.out" __lll_lock_wait (futex=futex@entry=0x5577249e9040 <mutex>, private=0) at lowlevellock.c:52
(gdb) thread 3
[Switching to thread 3 (Thread 0x7fa0254e0700 (LWP 172459))]
#0  __lll_lock_wait (futex=futex@entry=0x5577249e9040 <mutex>, private=0) at lowlevellock.c:52
52	lowlevellock.c: 没有那个文件或目录.
(gdb) where
#0  __lll_lock_wait (futex=futex@entry=0x5577249e9040 <mutex>, private=0) at lowlevellock.c:52
#1  0x00007fa025ee20a3 in __GI___pthread_mutex_lock (mutex=0x5577249e9040 <mutex>) at ../nptl/pthread_mutex_lock.c:80
#2  0x00005577249e62f7 in func_b (n=0x0) at pthreads.c:28
#3  0x00007fa025edf609 in start_thread (arg=<optimized out>) at pthread_create.c:477
#4  0x00007fa025e04133 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
(gdb) frame 2
#2  0x00005577249e62f7 in func_b (n=0x0) at pthreads.c:28
28		pthread_mutex_lock(&mutex);
(gdb) print tid
$3 = 172459
(gdb) print mutex
$4 = pthread_mutex_t = {Type = Normal, Status = Acquired, possibly with waiters, Owner ID = 172458, Robust = No, Shared = No, Protocol = None}
(gdb) 

#endif

pthread_mutex_t mutex;
int a = 0, b = 0;
int x = 0, y = 0;

void *func_a(void *n)
{
	pthread_mutex_lock(&mutex);
	pid_t tid = syscall(SYS_gettid);
	a = 1;
	x = b;
	pid_t pid = getpid();
	while (1) {
		sleep(1);
	}
	return NULL;
}

void *func_b(void *n)
{
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	pthread_mutex_lock(&mutex);
	b = 1;
	y = a;
	while (1) {
		sleep(1);
	}
	return NULL;
}

int main(void)
{

#if 0
       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
pthread_mutex_lock(3), pthread_mutex_unlock(3)
       int pthread_mutex_lock(pthread_mutex_t *mutex);
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
       int pthread_mutex_unlock(pthread_mutex_t *mutex);
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
           const pthread_mutexattr_t *restrict attr);
#endif
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
       pthread_mutex_init(&mutex, NULL);
	pthread_t thread = 0, thread_2 = 0;
       pthread_create(&thread , NULL,
                         func_a, NULL);
       pthread_create(&thread_2, NULL,
                         func_b, NULL);
	pthread_join(thread, NULL);
	pthread_join(thread_2, NULL);
	printf("x :%d, y:%d\n", x, y);
	pthread_mutex_destroy(&mutex);
	return 0;
}
