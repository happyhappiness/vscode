apr_status_t apr_socket_data_set(apr_socket_t *sock, void *data, const char *key,
                                 apr_status_t (*cleanup) (void *))
{
    sock_userdata_t *new = apr_palloc(sock->pool, sizeof(sock_userdata_t));

    new->key = apr_pstrdup(sock->pool, key);
    new->data = data;
    new->next = sock->userdata;
    sock->userdata = new;

    if (cleanup) {
        apr_pool_cleanup_register(sock->pool, data, cleanup, cleanup);
    }

    return APR_SUCCESS;
}