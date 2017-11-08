apr_status_t apr_socket_create(apr_socket_t **new, int family, int type,
                               apr_pool_t *cont)
{
    return apr_socket_create_ex(new, family, type, 0, cont);
}