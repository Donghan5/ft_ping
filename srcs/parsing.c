#include "ft_ping.h"

void	ft_parse_args(int argc, char **argv, t_ping_info *info)
{
    int i;
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;

    i = 1;
    while (i < argc)
    {
        char option;

        option = argv[i][1];
        if (argv[i][0] == '-')
        {
            if (option == 'v')
                info->flags |= FLAG_VERBOSE;
            else if (option == 'f')
                info->flags |= FLAG_FLOOD;
            else if (option == 'l')
            {
                info->flags |= FLAG_PRELOAD;
                if (argv[i + 1] && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
                {
                    info->preload = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                    exit(1);
                }
            }
            else if (option == 'n')
                info->flags |= FLAG_NUMERIC;
            else if (option == 'w')
            {
                info->flags |= FLAG_DEADLINE;
                if (argv[i + 1] && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
                {
                    info->deadline = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                    exit(1);
                }
            }
            else if (option == 'W')
            {
                info->flags |= FLAG_TIMEOUT;
                if (argv[i + 1] && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
                {
                    info->timeout = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                    exit(1);
                }
            }
            else if (option == 'p')
            {
                info->flags |= FLAG_PREFILL;
                if (argv[i + 1])
                {
                    info->prefill = argv[i + 1];
                    i++;
                }
                else
                {
                    fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                    exit(1);
                }
            }
            else if (option == 'r')
                info->flags |= FLAG_RANDOM_DATA;
            else if (option == 's')
            {
                info->flags |= FLAG_PACKET_SIZE;
                if (argv[i + 1] && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9')
                {
                    info->packet_size = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                    exit(1);
                }
            }
            else if (option == 'T')
                info->flags |= FLAG_TIMESTAMP;
            else if (option == '?')
                info->flags |= FLAG_HELP;
            else if (option == '-')
                printf("future implement\n");
            else
            {
                fprintf(stderr, "ft_ping: invalid option -- '%s'\n", argv[i]);
                exit(1);
            }
        }
        else
        {
            // --- hostname or ip address ---
            info->hostname = argv[i];
            if (getaddrinfo(info->hostname, NULL, &hints, &res))
            {
                fprintf(stderr, "ft_ping: hostname not found: %s\n", info->hostname);
                exit(1);
            }
            info->target = *(struct sockaddr_in *)res->ai_addr;
            freeaddrinfo(res);
        }
        i++;
    }
    if (!info->hostname)
    {
        fprintf(stderr, "ft_ping: hostname not provided\n");
        exit(1);
    }
}