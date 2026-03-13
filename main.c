#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
    // -- TODO: Implement the main function to demonstrate the usage of inet functions after adding flag options -- //
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <IP_ADDRESS>\n", argv[0]);
        return (1);
    }

    ip_str = argv[1];

    bool is_ip;
    truct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));   

    is_ip = inet_pton(AF_INET, ip_str, &ip_addr);
    printf("Converted IP address: %s\n", inet_ntoa(ip_addr));

    if (is_ip == 1)
    {
        printf("Valid IP address: %s\n", ip_str);
        printf("Doing ping directly to the IP address...\n");   
    }
    else if (is_ip == 0)
    {
        printf("Domain name provided: %s\n", ip_str);
        printf("Resolving domain name to IP address...\n");
        if (getaddrinfo(ip_str, NULL, &hints, &result) == 0)
        {
            printf("Resolved IP address: %s\n", inet_ntoa(((struct sockaddr_in *)result->ai_addr)->sin_addr));
            printf("Doing ping to the resolved IP address...\n");
        }
        else
        {
            fprintf(stderr, "Failed to resolve domain name: %s\n", ip_str);
            return (1);
        }
    }
    else
    {
        fprintf(stderr, "Invalid input: %s\n", ip_str);
        printf("Please provide a valid IP address or domain name.\n");
        return (1);
    }

    return (0);
}