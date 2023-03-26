#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	char* ifname = "enp0s25";
	unsigned char dstMac[6] = {0x52, 0x54, 0x00, 0x3f, 0xa2, 0xe8};
	int fd = socket(PF_PACKET, SOCK_RAW, htons(0x2022));

	struct ifreq req = {};
	struct sockaddr_ll addr = {};
#define LENGTH 60
	unsigned char txPkt[LENGTH];
	unsigned char rxPkt[LENGTH];
	struct ethhdr *expect_hdr = (void*)txPkt;

	/* get index for bind */
	strcpy((char*)req.ifr_name, (char*)ifname);
	if (ioctl(fd, SIOCGIFINDEX, &req) < 0) {
		fprintf(stderr, "init: ioctl error :%m\n");
		goto err;
	}

	/* bind to interface */
	addr.sll_family   = PF_PACKET;
	addr.sll_protocol = 0;
	addr.sll_ifindex  = req.ifr_ifindex;
	addr.sll_protocol = htons(0x2022);
#if 1
	if (bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "init: bind fails error :%m\n");
		goto err;
	}
#endif

	/* get mac address for source mac */
	if (ioctl(fd, SIOCGIFHWADDR, &req) < 0) {
		fprintf(stderr, "init: ioctl SIOCGIFHWADDR error :%m\n");
		goto err;
	}

	/* store your mac address somewhere you'll need it! in your packet */
	memcpy(expect_hdr->h_source, (unsigned char*)req.ifr_hwaddr.sa_data, ETH_ALEN);
	memcpy(expect_hdr->h_dest, dstMac, ETH_ALEN);
	expect_hdr->h_proto = htons(0x2022);
	memset(txPkt + sizeof(*expect_hdr), 0x34, sizeof(txPkt) - sizeof(*expect_hdr));

	/* add more data, like a type field!  etc */

	while (1) {
#if 0
		recv(fd, rxPkt, 60, 0);
		fprintf(stdout, "rxPkt + sizeof(*expect_hdr):%s\n",
			rxPkt + sizeof(*expect_hdr));
#endif
		send(fd, txPkt, LENGTH, 0);
		sleep(2);
	}

	if (fd <= fd) {
		close(fd);
		fd = -1;
	}
	return 0;
err:
	if (fd <= fd) {
		close(fd);
		fd = -1;
	}
	return -1;
}

