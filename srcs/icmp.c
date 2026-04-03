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
	int		total_size;
	char	buffer[total_size];

	total_size = sizeof(struct icmphdr) + info->packet_size;

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

void	ft_receive_icmp_packet(t_ping_info *info)
{
	char	buffer[1024];
	struct iphdr	*ip;
	struct icmphdr	*icmp;
	struct timeval	recv_time;
	struct timeval	send_time;
	double rtt;
	
	if (recvfrom(info->socket, buffer, sizeof(buffer), 0, NULL, NULL) == -1)
	{
		perror("ft_ping: recvfrom error");
		return ;
	}
	
	// --- receive time --- //
	gettimeofday(&info->recv_time, NULL);
	
	// --- skip ip header and check icmp header --- //
	
	ip = (struct iphdr *)buffer;
	icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));
	
	// --- verify type, identifier --- //
	if (icmp->type != ICMP_ECHOREPLY)
	{
		if (info->flags & FLAG_VERBOSE)
			fprintf(stderr, "Fail to check the type. Please verify it");
		return;
	}

	if (icmp->un.echo.id != getpid())
	{
		if (info->flags & FLAG_VERBOSE)
			fprintf(stderr, "Not match the process. Please verify it");
		return;
	}
	// --- calculate rtt and update stats --- //
	send_time = info->send_time;
	recv_time = info->recv_time;
	rtt = (recv_time.tv_sec - send_time.tv_sec) * 1000.0 + (recv_time.tv_usec - send_time.tv_usec) / 1000.0;
	
	info->received++;
	info->total_rtt += rtt;
	if (rtt < info->min_rtt || info->min_rtt == 0)
		info->min_rtt = rtt;
	if (rtt > info->max_rtt)
		info->max_rtt = rtt;
}