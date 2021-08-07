#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
/* #include <net/if.h> */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>



struct arpdata {
	unsigned char		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char		ar_sip[4];		/* sender IP address		*/
	unsigned char		ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char		ar_tip[4];		/* target IP address		*/
};

int main(int argc, char *argv[])
{
	char buff[sizeof(struct ethhdr) + sizeof(struct arphdr) + sizeof(struct arpdata)] = {};
	struct ethhdr *ethhdr = NULL;
	struct arphdr *arphdr = NULL;
	struct arpdata *arpdata = NULL;
	ethhdr = (struct ethhdr *)buff;
	arphdr = (struct arphdr *)(buff + sizeof(struct ethhdr));
	arpdata = (struct arpdata *)(buff + sizeof(struct ethhdr) + sizeof(struct arphdr));
#if 0
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	__be16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));
#endif
	int fd = -1;
	fd = socket(AF_INET, SOCK_PACKET, htons(ETH_P_ARP));
	if (-1 == fd) {
		fprintf(stderr, "socket error :%m\n");
		exit(EXIT_FAILURE);
	} 
	memset(ethhdr->h_dest, 0xff, sizeof(ethhdr->h_dest));
	struct ifreq ifreq = {.ifr_name = "wlo1"};

	if (-1 == ioctl(fd, SIOCGIFHWADDR, &ifreq)) {
		fprintf(stderr, "ioctl error :%m\n");
		exit(EXIT_FAILURE);
	}
#if 0
           struct sockaddr {
               sa_family_t sa_family;
               char        sa_data[14];
           }
#endif
	fprintf(stdout, "ifreq.ifr_hwaddr.sa_data:");
	int i = 0;
	unsigned char *tmphwaddr = NULL;
	tmphwaddr = ifreq.ifr_hwaddr.sa_data;
	for (i = 0; i < sizeof(ifreq.ifr_hwaddr.sa_data); i++) {
		fprintf(stdout, "%02x:", tmphwaddr[i]);
	}
	putchar('\n');

	memcpy(ethhdr->h_source, ifreq.ifr_hwaddr.sa_data, ETH_ALEN);
	for (i = 0; i < sizeof(ethhdr->h_source); i++) {
		fprintf(stdout, "%02x:", ethhdr->h_source[i]);
	}
	putchar('\n');

	ethhdr->h_proto = htons(ETH_P_ARP);
#if 0

struct arphdr {
	__be16		ar_hrd;		/* format of hardware address	*/
	__be16		ar_pro;		/* format of protocol address	*/
	unsigned char	ar_hln;		/* length of hardware address	*/
	unsigned char	ar_pln;		/* length of protocol address	*/
	__be16		ar_op;		/* ARP opcode (command)		*/

#if 0
	 /*
	  *	 Ethernet looks like this : This bit is variable sized however...
	  */
	unsigned char		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char		ar_sip[4];		/* sender IP address		*/
	unsigned char		ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char		ar_tip[4];		/* target IP address		*/
#endif

};
#endif


	arphdr->ar_hrd = htons(ETH_P_802_3); 
	arphdr->ar_pro = htons(ETH_P_IP);
	arphdr->ar_hln = ETH_ALEN;
	arphdr->ar_pln = 4;
	arphdr->ar_op = htons(ARPOP_REQUEST);

#if 0
	 /*
	  *	 Ethernet looks like this : This bit is variable sized however...
	  */
	unsigned char		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char		ar_sip[4];		/* sender IP address		*/
	unsigned char		ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char		ar_tip[4];		/* target IP address		*/
#endif

	memcpy(arpdata->ar_sha, ethhdr->h_source, ETH_ALEN);
	ioctl(fd, SIOCGIFADDR, &ifreq);
	memcpy(arpdata->ar_sip, ifreq.ifr_dstaddr.sa_data + 2, 4);
	arpdata->ar_tip[0] = 192;
	arpdata->ar_tip[1] = 168;
	arpdata->ar_tip[2] = 124;
	arpdata->ar_tip[3] = 9;
	
#if 0
       #include <sys/types.h>
       #include <sys/socket.h>

       ssize_t send(int sockfd, const void *buf, size_t len, int flags);

       ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
#endif
	struct sockaddr dest_addr = {.sa_family = AF_INET, .sa_data = "wlo1"};
	if (-1 == sendto(fd, buff, sizeof(buff), 0, &dest_addr, sizeof(dest_addr))) {
		fprintf(stderr, "sendto error :%m\n");
	}

	char buff2[sizeof(struct ethhdr) + sizeof(struct arphdr) + sizeof(struct arpdata)] = {};
	struct ethhdr *ethhdr2 = NULL;
	struct arphdr *arphdr2 = NULL;
	struct arpdata *arpdata2 = NULL;
	ethhdr2 = (struct ethhdr *)buff2;
	arphdr2 = (struct arphdr *)(buff2 + sizeof(struct ethhdr));
	arpdata2 = (struct arpdata *)(buff2 + sizeof(struct ethhdr) + sizeof(struct arphdr));

	struct sockaddr dest_addr2 = {};
	int len = 0;
	recvfrom(fd, buff2, sizeof(buff2), 0, &dest_addr2, &len);
	fprintf(stdout, "recvfrom arphdr2->ar_op:%04x\n", ntohs(arphdr2->ar_op));

	for (i = 0; i < sizeof(ethhdr2->h_source); i++) {
		fprintf(stdout, "%02x:", ethhdr2->h_source[i]);
	}
	putchar('\n');

	return 0;
}
