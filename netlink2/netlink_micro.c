#include <stdio.h>
#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>


int main(void)
{

	fprintf(stdout, "NETLINK_ROUTE:%d\n", NETLINK_ROUTE);
#if 0
	fprintf(stdout, "NETLINK_W1:%d\n", NETLINK_W1);
#endif
	fprintf(stdout, "NETLINK_USERSOCK:%d\n", NETLINK_USERSOCK);
	fprintf(stdout, "NETLINK_FIREWALL:%d\n", NETLINK_FIREWALL);
	fprintf(stdout, "NETLINK_INET_DIAG:%d\n", NETLINK_INET_DIAG);
	fprintf(stdout, "NETLINK_NFLOG:%d\n", NETLINK_NFLOG);
	fprintf(stdout, "NETLINK_XFRM:%d\n", NETLINK_XFRM);
	fprintf(stdout, "NETLINK_SELINUX:%d\n", NETLINK_SELINUX);
	fprintf(stdout, "NETLINK_ISCSI:%d\n", NETLINK_ISCSI);
	fprintf(stdout, "NETLINK_AUDIT:%d\n", NETLINK_AUDIT);
	fprintf(stdout, "NETLINK_FIB_LOOKUP:%d\n", NETLINK_FIB_LOOKUP);
	fprintf(stdout, "NETLINK_CONNECTOR:%d\n", NETLINK_CONNECTOR);
	fprintf(stdout, "NETLINK_NETFILTER:%d\n", NETLINK_NETFILTER);
	fprintf(stdout, "NETLINK_IP6_FW:%d\n", NETLINK_IP6_FW);
	fprintf(stdout, "NETLINK_DNRTMSG:%d\n", NETLINK_DNRTMSG);
	fprintf(stdout, "NETLINK_KOBJECT_UEVENT:%d\n", NETLINK_KOBJECT_UEVENT);
	fprintf(stdout, "NETLINK_GENERIC:%d\n", NETLINK_GENERIC);
	fprintf(stdout, "NETLINK_CRYPTO:%d\n", NETLINK_CRYPTO);
	return 0;
}
