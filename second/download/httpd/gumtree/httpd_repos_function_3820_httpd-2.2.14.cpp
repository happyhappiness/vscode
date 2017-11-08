static void alloc_socket(apr_socket_t **new, apr_pool_t *p)
{
    *new = (apr_socket_t *)apr_pcalloc(p, sizeof(apr_socket_t));
    (*new)->pool = p;
    (*new)->local_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->pool,
                                                       sizeof(apr_sockaddr_t));
    (*new)->local_addr->pool = p;

    (*new)->remote_addr = (apr_sockaddr_t *)apr_pcalloc((*new)->pool,
                                                        sizeof(apr_sockaddr_t));
    (*new)->remote_addr->pool = p;
    (*new)->remote_addr_unknown = 1;

    /* Create a pollset with room for one descriptor. */
    /* ### check return codes */
    (void) apr_pollset_create(&(*new)->pollset, 1, p, 0);
}