static void set_socket_vars(apr_socket_t *sock, int family, int type, int protocol)
{
    sock->type = type;
    sock->protocol = protocol;
    apr_sockaddr_vars_set(sock->local_addr, family, 0);
    apr_sockaddr_vars_set(sock->remote_addr, family, 0);
#if APR_HAVE_IPV6
    /* hard-coded behavior for older Windows IPv6 */
    if (apr_os_level < APR_WIN_VISTA && family == AF_INET6) {
        apr_set_option(sock, APR_IPV6_V6ONLY, 1);
    }
#endif
}