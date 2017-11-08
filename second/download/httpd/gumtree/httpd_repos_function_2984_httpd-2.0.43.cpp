static void save_addrinfo(apr_pool_t *p, apr_sockaddr_t *sa, 
                          struct addrinfo *ai, apr_port_t port)
{
    sa->pool = p;
    memcpy(&sa->sa, ai->ai_addr, ai->ai_addrlen);
    apr_sockaddr_vars_set(sa, ai->ai_family, port);
}