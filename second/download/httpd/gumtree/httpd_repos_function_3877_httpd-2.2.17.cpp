static apr_status_t find_addresses(apr_sockaddr_t **sa, 
                                   const char *hostname, apr_int32_t family,
                                   apr_port_t port, apr_int32_t flags, 
                                   apr_pool_t *p)
{
    if (flags & APR_IPV4_ADDR_OK) {
        apr_status_t error = call_resolver(sa, hostname, AF_INET, port, flags, p);

#if APR_HAVE_IPV6
        if (error) {
            family = AF_INET6; /* try again */
        }
        else
#endif
        return error;
    }
#if APR_HAVE_IPV6
    else if (flags & APR_IPV6_ADDR_OK) {
        apr_status_t error = call_resolver(sa, hostname, AF_INET6, port, flags, p);

        if (error) {
            family = AF_INET; /* try again */
        }
        else {
            return APR_SUCCESS;
        }
    }
#endif

    return call_resolver(sa, hostname, family, port, flags, p);
}