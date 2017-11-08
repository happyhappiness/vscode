apr_status_t apr_socket_data_set(apr_socket_t *sock, void *data, const char *key,
                              apr_status_t (*cleanup) (void *))
{
    return apr_pool_userdata_set(data, key, cleanup, sock->cntxt);
}