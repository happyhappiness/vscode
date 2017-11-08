apr_status_t apr_os_sock_put(apr_socket_t **sock, apr_os_sock_t *thesock, 
                           apr_pool_t *cont)
{
    if ((*sock) == NULL) {
        alloc_socket(sock, cont);
        /* XXX IPv6 figure out the family here! */
        /* XXX figure out the actual socket type here */
        /* *or* just decide that apr_os_sock_put() has to be told the family and type */
        set_socket_vars(*sock, APR_INET, SOCK_STREAM);
        (*sock)->timeout = -1;
    }
    (*sock)->local_port_unknown = (*sock)->local_interface_unknown = 1;
    (*sock)->socketdes = *thesock;
    return APR_SUCCESS;
}