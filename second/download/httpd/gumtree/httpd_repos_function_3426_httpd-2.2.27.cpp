static void apr_setup(apr_pool_t *p, apr_socket_t **sock, int *family)
{
    apr_status_t rv;

    *sock = NULL;
    rv = apr_socket_create(sock, *family, SOCK_STREAM, 0, p);
    if (rv != APR_SUCCESS) {
        aprerr("apr_socket_create()", rv);
    }

    if (*family == APR_UNSPEC) {
        apr_sockaddr_t *localsa;

        rv = apr_socket_addr_get(&localsa, APR_LOCAL, *sock);
        if (rv != APR_SUCCESS) {
            aprerr("apr_socket_addr_get()", rv);
        }
        *family = localsa->family;
    }
}