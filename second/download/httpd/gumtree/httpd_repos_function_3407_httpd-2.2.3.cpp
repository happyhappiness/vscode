void apr_sockaddr_vars_set(apr_sockaddr_t *addr, int family, apr_port_t port)
{
    addr->family = family;
    addr->sa.sin.sin_family = family;
    if (port) {
        /* XXX IPv6: assumes sin_port and sin6_port at same offset */
        addr->sa.sin.sin_port = htons(port);
        addr->port = port;
    }

    if (family == APR_INET) {
        addr->salen = sizeof(struct sockaddr_in);
        addr->addr_str_len = 16;
        addr->ipaddr_ptr = &(addr->sa.sin.sin_addr);
        addr->ipaddr_len = sizeof(struct in_addr);
    }
#if APR_HAVE_IPV6
    else if (family == APR_INET6) {
        addr->salen = sizeof(struct sockaddr_in6);
        addr->addr_str_len = 46;
        addr->ipaddr_ptr = &(addr->sa.sin6.sin6_addr);
        addr->ipaddr_len = sizeof(struct in6_addr);
    }
#endif
}