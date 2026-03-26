#include "ft_ping.h"

// --- init ping info, boolean default value set to false --- //
void    ft_init_ping_info(t_ping_info *info)
{
    info->socket = -1;
    info->hostname = NULL;
    info->flags = 0;
    info->target = (struct sockaddr_in){0};
    info->send_time = (struct timeval){0};
    info->recv_time = (struct timeval){0};
    info->sequence = 0;
    info->packet_size = 56;
    info->ttl = 64;
    info->timeout = 1000;
    info->interval = 1000;
    info->count = 0;
    info->received = 0;
    info->sent = 0;
    info->lost = 0;
    info->min_rtt = 0;
    info->max_rtt = 0;
    info->avg_rtt = 0;
    info->total_rtt = 0;
	info->preload = 0;
	info->deadline = 0;
	info->prefill = NULL;
}

// --- init signal handler for ctrl c --- //
void	ft_init_signal_handler(void)
{
    struct sigaction	sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = ft_signal_handler;
    sigaction(SIGINT, &sa, NULL);
}

// --- signal handler for ctrl c print with stats and exit --- //
void	ft_signal_handler(int signum)
{
    if (signum == SIGINT)
	{
		ft_print_stats(g_ping_info);
        exit(0);
    }
}