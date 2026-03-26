#include "ft_ping.h"

// --- Create socket, setting 1. TTL 2. Timeout --- //
void    ft_create_socket(t_ping_info *info)
{
    int socket_fd;
    int ttl;
    struct timeval timeout;

    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    ttl = info->ttl;
    timeout.tv_sec = info->timeout / 1000;
    timeout.tv_usec = info->timeout % 1000 * 1000;

    if (socket_fd == -1)
    {
        fprintf(stderr, "ft_ping: create socket errror");
        exit(EXIT_FAILURE);
    }
    info->socket = socket_fd;

    if (setsockopt(info->socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
    {
        fprintf(stderr, "ft_ping: setsockopt errror");
        close(info->socket);
        exit(EXIT_FAILURE);
    }

    if (setsockopt(info->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)))
    {
        fprintf(stderr, "ft_ping: setsockopt errror");
        close(info->socket);
        exit(EXIT_FAILURE);
    }
}