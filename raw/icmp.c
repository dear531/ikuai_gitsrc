#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <unistd.h>


#if 0
struct iphdr
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ihl:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int ihl:4;
#else
# error	"Please fix <bits/endian.h>"
#endif
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
    u_int16_t frag_off;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
    /*The options start here. */
  };

struct icmphdr
{
  u_int8_t type;		/* message type */
  u_int8_t code;		/* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t	id;
      u_int16_t	sequence;
    } echo;			/* echo datagram */
    u_int32_t	gateway;	/* gateway address */
    struct
    {
      u_int16_t	__glibc_reserved;
      u_int16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
# define ODDBYTE(v)	(v)
#elif BYTE_ORDER == BIG_ENDIAN
# define ODDBYTE(v)	((u_short)(v) << 8)
#else
# define ODDBYTE(v)	htons((u_short)(v) << 8)
#endif

u_short
in_cksum(const u_short *addr, register int len, u_short csum)
{
	register int nleft = len;
	const u_short *w = addr;
	register u_short answer;
	register int sum = csum;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft == 1)
		sum += ODDBYTE(*(u_char *)w); /* le16toh() may be unavailable on old systems */

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

#define ICMP_DATA_LEN 56
#define DATA_LEN (sizeof(struct iphdr) + sizeof(struct icmphdr) + ICMP_DATA_LEN)
int main(int argc, char *argv[])
{
	struct iphdr *iphd = NULL;
	struct icmphdr *icmphd = NULL;
	char data[DATA_LEN] = {};
	char rdata[DATA_LEN] = {};
	iphd = (void *)data;
	icmphd = (void *)data + sizeof(struct iphdr);
	printf("iphd->tos:%d\n", iphd->tos);
	printf("iphd->tos:%d\n", iphd->tos);
	printf("iphd->tos:%d\n", iphd->tos);

	printf("icmphd->type:%d\n", icmphd->type);
	printf("icmphd->type:%d\n", icmphd->type);
	printf("icmphd->type:%d\n", icmphd->type);
#if 0
       #include <sys/types.h>          /* See NOTES */
       #include <sys/socket.h>

       int socket(int domain, int type, int protocol);

#endif
	int fd = -1;
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (-1 == fd) {
		fprintf(stderr, "raw socket icmp failed :%m\n");
		goto out;
	}

	int iphf = 1;
	if (-1 == setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &iphf, sizeof(iphf))) {
		fprintf(stderr, "raw socket icmp failed :%m\n");
		goto out;
	}

#if 0
struct iphdr
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ihl:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int ihl:4;
#else
# error	"Please fix <bits/endian.h>"
#endif
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
    u_int16_t frag_off;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
    /*The options start here. */
  };
#include <netinet/ip.h>
#endif
	iphd->ihl = sizeof(struct iphdr) >> 2;
	iphd->version = IPVERSION;
	iphd->id = 0;
	iphd->ttl = MAXTTL;
	iphd->saddr = inet_addr("192.168.3.122");
	iphd->tot_len = htons(DATA_LEN);
	iphd->protocol = IPPROTO_ICMP;
	iphd->daddr = inet_addr("220.181.112.244");
#if 0
in_addr_t inet_addr(const char *cp);
#endif

#if 0
struct icmphdr
{
  u_int8_t type;		/* message type */
  u_int8_t code;		/* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t	id;
      u_int16_t	sequence;
    } echo;			/* echo datagram */
    u_int32_t	gateway;	/* gateway address */
    struct
    {
      u_int16_t	__glibc_reserved;
      u_int16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};
#include <netinet/ip_icmp.h>
#endif
	
	icmphd->type = ICMP_ECHO;
	icmphd->un.echo.id = getpid();
	icmphd->checksum = in_cksum((unsigned short *)icmphd, DATA_LEN - sizeof(struct iphdr), 0);
#if 0
       ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
           struct sockaddr_in {
               sa_family_t    sin_family; /* address family: AF_INET */
               in_port_t      sin_port;   /* port in network byte order */
               struct in_addr sin_addr;   /* internet address */
           };

           /* Internet address. */
           struct in_addr {
               uint32_t       s_addr;     /* address in network byte order */
           };

#endif
#if 1
	struct sockaddr_in daddr = {};
	struct sockaddr_in rdaddr = {};
	daddr.sin_family = AF_INET;
	daddr.sin_addr.s_addr = inet_addr("220.181.112.244");
	int len = 0;
	while (1) {
		if (-1 == sendto(fd, data, sizeof(data), 0,
			(const struct sockaddr *)&daddr, sizeof(daddr))) {
			fprintf(stderr, "sendto error :%m\n");
			goto out;
		}
#if 0
       ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

#endif
		if (-1 == recvfrom(fd, rdata, sizeof(rdata), 0,
			(struct sockaddr *)&rdaddr, &len)) {
			fprintf(stderr, "recvfrom error :%m\n");
			goto out;
		}
		iphd = (void *)rdata;
		icmphd = (void *)rdata + (iphd->ihl << 2);
#if 0
char *inet_ntoa(struct in_addr in);
#endif
		struct in_addr tmp = {};
		tmp.s_addr = iphd->saddr;
		fprintf(stdout, "iphd->daddr:%s, ttl:%d\n",
			inet_ntoa(tmp), iphd->ttl);
		fprintf(stdout, "type:%d, un.echo.id:%d, checksum:%x\n",
			icmphd->type, icmphd->un.echo.id, icmphd->checksum);
		sleep(1);
	}
#else
	while (1) {
		send(fd, data, sizeof(data), 0);
		sleep(1);
	}
#endif
out:
	if (0 >= fd) {
		close(fd);
		fd = -1;
	}

	return 0;
}
