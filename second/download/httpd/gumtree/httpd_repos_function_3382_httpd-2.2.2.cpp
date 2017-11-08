static int sock_is_ipv4(apr_socket_t *sock)
{
    if (sock->local_addr->family == APR_INET)
        return 1;
    return 0;
}