#include <stdio.h>
#include <sys/utsname.h>

#if 0
           struct utsname {
               char sysname[];    /* Operating system name (e.g., "Linux") */
               char nodename[];   /* Name within "some implementation-defined
                                     network" */
               char release[];    /* Operating system release (e.g., "2.6.28") */
               char version[];    /* Operating system version */
               char machine[];    /* Hardware identifier */
           #ifdef _GNU_SOURCE
               char domainname[]; /* NIS or YP domain name */
           #endif
           };
#endif



int main(void)
{
	struct utsname buf;
	uname(&buf);
	printf("buf.sysname:%s\nbuf.nodename:%s\nbuf.release:%s\nbuf.version:%s\nbuf.machine:%s\n"
           #ifdef _GNU_SOURCE
               "buf.domainname:%s\n"
           #endif
,
               buf.sysname, buf.nodename, buf.release, buf.version, buf.machine
           #ifdef _GNU_SOURCE
               ,buf.domainname
           #endif
);
	return 0;
}
