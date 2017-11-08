apr_status_t apr_socket_data_get(void **data, const char *key, apr_socket_t *sock)
{
    return apr_pool_userdata_get(data, key, sock->cntxt);
}