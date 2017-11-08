static int sock_is_ipv6(apr_socket_t *sock)
{
    if (sock->local_addr->family == APR_INET6)
        return 1;
    return 0;
}