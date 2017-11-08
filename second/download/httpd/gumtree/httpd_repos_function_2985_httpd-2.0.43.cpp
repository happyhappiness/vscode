static void save_addrinfo(apr_pool_t *p, apr_sockaddr_t *sa,
                          struct in_addr ipaddr, apr_port_t port)
{
    sa->pool = p;
    sa->sa.sin.sin_addr = ipaddr;
    apr_sockaddr_vars_set(sa, AF_INET, port);
}