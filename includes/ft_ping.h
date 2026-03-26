#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
#include <signal.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// --- flags --- //
#define FLAG_VERBOSE	    (1 << 0)
#define FLAG_FLOOD		    (1 << 1)
#define FLAG_NUMERIC	    (1 << 2)
#define FLAG_TTL		    (1 << 3)
#define FLAG_TIMEOUT	    (1 << 4)
#define FLAG_INTERVAL	    (1 << 5)
#define FLAG_COUNT		    (1 << 6)
#define FLAG_PACKET_SIZE	(1 << 7)
#define FLAG_PREFILL	    (1 << 8)
#define FLAG_RANDOM_DATA	(1 << 9)
#define FLAG_TIMESTAMP		(1 << 10)
#define FLAG_HELP			(1 << 11)
#define FLAG_PRELOAD	    (1 << 12)
#define FLAG_PACKET_SIZE	(1 << 13)
#define FLAG_DEADLINE	    (1 << 14)

typedef struct s_ping_info
{
    int					socket;
    char				*hostname;
    uint32_t			flags;
    struct sockaddr_in	target;
    struct timeval		send_time;
    struct timeval		recv_time;
    uint32_t			sequence;
    uint32_t			packet_size;
    uint32_t			ttl;
    uint32_t			timeout;
    uint32_t			interval;
    uint32_t			count;
    uint32_t			received;
    uint32_t			sent;
    uint32_t			preload;
    uint32_t			lost;
	uint32_t			deadline;
	char				*prefill;
    double				min_rtt;
    double				max_rtt;
    double				avg_rtt;
    double				total_rtt;
}   t_ping_info;

extern t_ping_info		*g_ping_info;
// --- utils --- //
void	ft_init_ping_info(t_ping_info *info);
void	ft_init_signal_handler(void);
void	ft_signal_handler(int signum);

// --- parsing --- //
void	ft_parse_args(int argc, char **argv, t_ping_info *info);

// --- print_info --- //
void	ft_print_stats(t_ping_info *info);

// --- socket --- //
void	ft_create_socket(t_ping_info *info);

#endif
// --- end of ft_ping.h --- //