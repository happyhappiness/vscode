static apr_status_t talkTalk(apr_socket_t *socket, apr_pool_t *parent)
{
    apr_pool_t *pool;
    apr_size_t len;
    char *buf;
    apr_status_t rv;

    if (apr_pool_create(&pool, parent) != APR_SUCCESS)
        return APR_ENOPOOL;


    buf = apr_palloc(pool, BUF_SIZE);
    if (!buf)
        return ENOMEM;

    do {
        len = BUF_SIZE;
        rv = apr_socket_recv(socket, buf, &len);
        if (APR_STATUS_IS_EOF(rv) || len == 0 || rv != APR_SUCCESS)
            break;
        rv = apr_socket_send(socket, buf, &len);
        if (len == 0 || rv != APR_SUCCESS)
            break;
    } while (rv == APR_SUCCESS);

    apr_pool_clear(pool);
    return APR_SUCCESS;
}