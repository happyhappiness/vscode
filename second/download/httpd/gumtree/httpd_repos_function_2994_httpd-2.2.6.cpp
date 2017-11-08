static void apr_setup(apr_pool_t **p, apr_socket_t **sock, int *family)
{
    char buf[120];
    apr_status_t rv;

    rv = apr_initialize();
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_initialize()->%d/%s\n",
                rv,
                apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    atexit(apr_terminate);

    rv = apr_pool_create(p, NULL);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_pool_create()->%d/%s\n",
                rv,
                apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    *sock = NULL;
    rv = apr_socket_create(sock, *family, SOCK_STREAM, 0, *p);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "apr_socket_create()->%d/%s\n",
                rv,
                apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    if (*family == APR_UNSPEC) {
        apr_sockaddr_t *localsa;

        rv = apr_socket_addr_get(&localsa, APR_LOCAL, *sock);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "apr_socket_addr_get()->%d/%s\n",
                    rv,
                    apr_strerror(rv, buf, sizeof buf));
            exit(1);
        }
        *family = localsa->family;
    }
}