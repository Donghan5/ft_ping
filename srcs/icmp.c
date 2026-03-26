#include "ft_ping.h"

static uint16_t	ft_checksum(uint16_t *buffer, int size)
{
	uint32_t sum;

	sum = 0;
	while (size > 1)
	{
		sum += *buffer++;
		size -= 2;
	}
	if (size == 1)
		sum += *(uint8_t *)buffer;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ((uint16_t)~sum);
}

void	ft_make_icmp_packet(t_ping_info *info)
{
	struct icmphdr	*icmp;
	int total_size;

	total_size = sizeof(struct icmphdr) + info->packet_size;
	char buffer[total_size];

	memset(buffer, 0, total_size);
	icmp = (struct icmphdr *)buffer;
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = info->sequence;
	
	icmp->checksum = ft_checksum((uint16_t *)buffer, total_size);
	
	gettimeofday(&info->send_time, NULL);
	
	if (sendto(info->socket, buffer, total_size, 0, \
				(struct sockaddr *)&info->target, sizeof(info->target)) == -1)
		perror("sendto");
	info->sent++;
	info->sequence++;
}