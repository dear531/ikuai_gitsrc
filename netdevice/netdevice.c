#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/capability.h>
#include <string.h>
#if 0
       #include <sys/socket.h>
       #include <netinet/in.h>
       #include <netinet/ip.h> /* superset of previous */
#endif

struct name_value_macro {
	char *name;
	int value;
} active[] = {
	{"IFF_UP", IFF_UP,},
	{"IFF_BROADCAST", IFF_BROADCAST,},
	{"IFF_DEBUG", IFF_DEBUG,},
	{"IFF_LOOPBACK", IFF_LOOPBACK,},
	{"IFF_POINTOPOINT", IFF_POINTOPOINT,},
	{"IFF_RUNNING", IFF_RUNNING,},
	{"IFF_NOARP", IFF_NOARP,},
	{"IFF_PROMISC", IFF_PROMISC,},
	{"IFF_NOTRAILERS", IFF_NOTRAILERS,},
	{"IFF_ALLMULTI", IFF_ALLMULTI,},
	{"IFF_MASTER", IFF_MASTER,},
	{"IFF_SLAVE", IFF_SLAVE,},
	{"IFF_MULTICAST", IFF_MULTICAST,},
	{"IFF_PORTSEL", IFF_PORTSEL,},
	{"IFF_AUTOMEDIA", IFF_AUTOMEDIA,},
	{"IFF_DYNAMIC", IFF_DYNAMIC,},
};

#if 0
struct name_value_macro extended[] = {
	{"IFF_802_1Q_VLAN", IFF_802_1Q_VLAN,},
	{"IFF_EBRIDGE", IFF_EBRIDGE,},
	{"IFF_SLAVE_INACTIVE", IFF_SLAVE_INACTIVE,},
	{"IFF_MASTER_8023AD", IFF_MASTER_8023AD,},
	{"IFF_MASTER_ALB", IFF_MASTER_ALB,},
	{"IFF_BONDING", IFF_BONDING,},
	{"IFF_SLAVE_NEEDARP", IFF_SLAVE_NEEDARP,},
	{"IFF_ISATAP", IFF_ISATAP,},
};
#endif

void perror_t(char *func_name)
{
       /* handle error */;
	fprintf(stderr, "%s error :%m\n", func_name);
}

void set_cap_raw()
{
	   cap_t caps;
           cap_value_t cap_list[1];

           if (!CAP_IS_SUPPORTED(CAP_SETFCAP))
		fprintf(stderr, "this system not supported\n");
		
           caps = cap_get_proc();
           if (caps == NULL) 
		perror_t("cap_get_proc");

           cap_list[0] = CAP_NET_RAW;
           if (cap_set_flag(caps, CAP_EFFECTIVE, 1, cap_list, CAP_SET) == -1)
		perror_t("cap_set_flag");

           if (cap_set_proc(caps) == -1)
		perror_t("cap_set_proc");

           if (cap_free(caps) == -1)
		perror_t("cap_free");
}

int main(int argc, char *argv[])
{
	int packet_socket = -1;
	struct ifreq inter = {};
#if 0
           struct ifreq {
               char ifr_name[IFNAMSIZ]; /* Interface name */
               union {
                   struct sockaddr ifr_addr;
                   struct sockaddr ifr_dstaddr;
                   struct sockaddr ifr_broadaddr;
                   struct sockaddr ifr_netmask;
                   struct sockaddr ifr_hwaddr;
                   short           ifr_flags;
                   int             ifr_ifindex;
                   int             ifr_metric;
                   int             ifr_mtu;
                   struct ifmap    ifr_map;
                   char            ifr_slave[IFNAMSIZ];
                   char            ifr_newname[IFNAMSIZ];
                   char           *ifr_data;
               };
           };
#endif
	set_cap_raw();

	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (-1 == packet_socket) {
		fprintf(stderr, "socket error :%m\n");
		goto out;
	}

	inter.ifr_ifindex = 1;
	ioctl(packet_socket, SIOCGIFNAME, &inter);
	fprintf(stdout, "SIOCGIFNAME\nifr_ifindex:%d - ifr_name:%s\n",
		inter.ifr_ifindex, inter.ifr_name);

	memset(&inter, 0x00, sizeof(inter));

	strcpy(inter.ifr_name, "wlo1");
	ioctl(packet_socket, SIOCGIFINDEX, &inter);
	fprintf(stdout, "SIOCGIFINDEX\nifr_name:%s - ifr_ifindex:%d\n",
		inter.ifr_name, inter.ifr_ifindex);

	ioctl(packet_socket, SIOCGIFFLAGS, &inter);
	fprintf(stdout, "SIOCGIFFLAGS\nifr_name:%s - inter.ifr_flags:%d\n",
		inter.ifr_name, inter.ifr_flags);

	int i = 0;
	for (i = 0; sizeof(active) / sizeof(*active) > i; i++) {
		if (active[i].value & inter.ifr_flags)
			fprintf(stdout, "ifr_flags contains %s\n", active[i].name);
	}

#if 0
	for (i = 0; sizeof(extended) / sizeof(*extended) > i; i++) {
		if (extended[i].value & inter.ifr_flags)
			fprintf(stdout, "ifr_flags contains %s\n", extended[i].name);
	}
#endif

	/* AF_INET socket for SIOCGIFINDEX */

#if 0
struct in_addr sin_addr;
struct sockaddr ifr_addr
           struct sockaddr {
               sa_family_t sa_family;
               char        sa_data[14];
           }
#endif

	strcpy(inter.ifr_name, "wlo1");
	ioctl(packet_socket, SIOCGIFINDEX, &inter);
	fprintf(stdout, "SIOCGIFINDEX\nifr_name:%s - ifr_ifindex:%d\n",
		inter.ifr_name, inter.ifr_ifindex);

	int tcp_socket = -1;
	struct ifreq tcp_inter = {};
	unsigned char *taddr = tcp_inter.ifr_addr.sa_data;
	strcpy(tcp_inter.ifr_name, "wlo1");

	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	ioctl(tcp_socket, SIOCGIFADDR, &tcp_inter);

	fprintf(stdout, "SIOCGIFADDR\nifr_name:%s - ifr_addr.sa_data:",
		tcp_inter.ifr_name);
	for (i = 0; i < sizeof(tcp_inter.ifr_addr.sa_data) / sizeof(*tcp_inter.ifr_addr.sa_data); i++) {
		fprintf(stdout, "%d.", taddr[i]);
	}
	putchar('\n');

	ioctl(tcp_socket, SIOCGIFDSTADDR, &tcp_inter);
	fprintf(stdout, "SIOCGIFDSTADDR\nifr_name:%s - ifr_dstaddr.sa_data:",
		tcp_inter.ifr_name);
	for (i = 0; i < sizeof(tcp_inter.ifr_dstaddr.sa_data) / sizeof(*tcp_inter.ifr_dstaddr.sa_data); i++) {
		fprintf(stdout, "%d.", taddr[i]);
	}
	putchar('\n');

	ioctl(tcp_socket, SIOCGIFNETMASK, &tcp_inter);
	fprintf(stdout, "SIOCGIFNETMASK\nifr_name:%s - ifr_dstaddr.sa_data:",
		tcp_inter.ifr_name);
	for (i = 0; i < sizeof(tcp_inter.ifr_dstaddr.sa_data) / sizeof(*tcp_inter.ifr_dstaddr.sa_data); i++) {
		fprintf(stdout, "%d.", taddr[i]);
	}
	putchar('\n');
#if 0
                  struct ifconf {
                      int                 ifc_len; /* size of buffer */
                      union {
                          char           *ifc_buf; /* buffer address */
                          struct ifreq   *ifc_req; /* array of structures */
                      };
                  };
#endif
	struct ifconf ifconf = {};
	ioctl(tcp_socket, SIOCGIFCONF, &ifconf);
	int j = 0;
	fprintf(stdout, "SIOCGIFCONF\n");
	if (NULL == ifconf.ifc_req) {
		fprintf(stdout, "ifconf.ifc_len:%d\n", ifconf.ifc_len);
	} else {
		for (i = 0; i < ifconf.ifc_len; i++) {
			fprintf(stdout, "SIOCGIFADDR\nifr_name:%s - ifr_addr.sa_data:",
				ifconf.ifc_req[i].ifr_name);
			for (j = 0; j < sizeof(ifconf.ifc_req[i].ifr_addr.sa_data) / sizeof(*ifconf.ifc_req[i].ifr_addr.sa_data); j++) {
				fprintf(stdout, "%d.", ifconf.ifc_req[i].ifr_addr.sa_data[i]);
			}
			putchar('\n');
		}
	}

	if (tcp_socket >= 0) {
		close(tcp_socket);
		tcp_socket = -1;
	}

	/* end for AF_INET socket */

	ioctl(packet_socket, SIOCGIFMETRIC, &inter);
	fprintf(stdout, "SIOCGIFMETRIC\nifr_name:%s - inter.ifr_metric:%d\n",
		inter.ifr_name, inter.ifr_metric);

#if 0
eo@HP:~/source/ikuai_gitsrc_ssh/netdevice$ ip link show wlo1
3: wlo1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP mode DORMANT group default qlen 1000
    link/ether 08:11:96:7d:08:f8 brd ff:ff:ff:ff:ff:ff
#endif
	ioctl(packet_socket, SIOCGIFHWADDR, &inter);
	taddr = inter.ifr_hwaddr.sa_data;
	fprintf(stdout, "SIOCGIFHWADDR\nifr_name:%s - ifr_hwaddr.sa_data:",
		inter.ifr_name);
	for (i = 0; i < sizeof(inter.ifr_hwaddr.sa_data) / sizeof(*inter.ifr_hwaddr.sa_data); i++) {
		fprintf(stdout, "%02x.", taddr[i]);
	}
	putchar('\n');

#if 0
                  struct ifmap {
                      unsigned long   mem_start;
                      unsigned long   mem_end;
                      unsigned short  base_addr;
                      unsigned char   irq;
                      unsigned char   dma;
                      unsigned char   port;
                  };
#endif

	strcpy(inter.ifr_name, "enp0s25");
	ioctl(packet_socket, SIOCGIFMAP, &inter);
	fprintf(stdout, "SIOCGIFMAP\nifr_name:%s - inter\n",
		inter.ifr_name);
	fprintf(stdout, "inter.ifr_map.mem_start:%lx\n", inter.ifr_map.mem_start);
	fprintf(stdout, "inter.ifr_map.mem_end:%lx\n", inter.ifr_map.mem_end);
	fprintf(stdout, "inter.ifr_map.base_addr:%x\n", inter.ifr_map.base_addr);
	fprintf(stdout, "inter.ifr_map.irq:%d\n", inter.ifr_map.irq);
	fprintf(stdout, "inter.ifr_map.dma:%d\n", inter.ifr_map.dma);
	fprintf(stdout, "inter.ifr_map.port:%d\n", inter.ifr_map.port);

	strcpy(inter.ifr_name, "wlo1");
	ioctl(packet_socket, SIOCGIFHWADDR, &inter);
	taddr = inter.ifr_hwaddr.sa_data;
	fprintf(stdout, "SIOCGIFHWADDR\nifr_name:%s - ifr_hwaddr.sa_data:",
		inter.ifr_name);
	for (i = 0; i < sizeof(inter.ifr_hwaddr.sa_data) / sizeof(*inter.ifr_hwaddr.sa_data); i++) {
		fprintf(stdout, "%02x.", taddr[i]);
	}
	putchar('\n');

	ioctl(packet_socket, SIOCGIFTXQLEN, &inter);
	fprintf(stdout, "SIOCGIFTXQLEN\nifr_name:%s - inter.ifr_qlen:%d\n",
		inter.ifr_name, inter.ifr_qlen);

	

out:
	if (0 <= packet_socket) {
		close(packet_socket);
		packet_socket = -1;
	}

	return 0;
}
