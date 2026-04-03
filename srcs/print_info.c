#include "ft_ping.h"

// --- print statistics --- //
void	ft_print_stats(t_ping_info *info)
{
    printf("\n--- %s ping statistics ---\n", info->hostname);
	if (info->sent > 0)
	{
		printf("%u packets transmitted, %u received, %.2f%% packet loss\n",
			info->sent, info->received, (info->sent - info->received) * 100.0 / info->sent);
	}
	if (info->received > 0)
		printf("rtt min/avg/max = %.3f/%.3f/%.3f ms\n", info->min_rtt, info->total_rtt / info->received, info->max_rtt);
}