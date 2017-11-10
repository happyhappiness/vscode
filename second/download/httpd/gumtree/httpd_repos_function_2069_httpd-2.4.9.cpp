static apr_status_t get_socket_from_path(apr_pool_t *p,
                                         const char* path,
                                         apr_socket_t **out_sock)
{
    struct sockaddr_un sa;
    apr_socket_t *s;
    apr_status_t rv;
    *out_sock = NULL;

    rv = apr_socket_create(&s, AF_UNIX, SOCK_STREAM, 0, p);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    sa.sun_family = AF_UNIX;
    apr_cpystrn(sa.sun_path, path, sizeof(sa.sun_path));

    rv = socket_connect_un(s, &sa);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    *out_sock = s;

    return APR_SUCCESS;
}