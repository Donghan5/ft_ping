#include "ft_ping.h"

t_ping_info	*g_ping_info;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [-v (options)] <IP_ADDRESS>\n", argv[0]);
        return (1);
    }

    // --- init ping info --- //
    
    // --- init signal handler --- //

    // --- parse arguments --- //

    // --- socket open --- //
    
    // --- main loop --- //

    // --- close program, print stats(info) and clean resources --- //

    return (0);
}