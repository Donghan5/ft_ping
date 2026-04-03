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
    t_ping_info info;
    ft_init_ping_info(&info);
    
    // --- init signal handler --- //
    ft_init_signal_handler();
    
    // --- parse arguments --- //

    // --- socket open --- //
    
    // --- main loop --- //

    // --- close program, print stats(info) and clean resources --- //

    return (0);
}