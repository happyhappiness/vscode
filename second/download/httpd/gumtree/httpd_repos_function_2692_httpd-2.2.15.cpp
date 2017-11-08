static apr_status_t get_server_line(apr_memcache_conn_t *conn)
{
    apr_size_t bsize = BUFFER_SIZE;
    apr_status_t rv = APR_SUCCESS;

    rv = apr_brigade_split_line(conn->tb, conn->bb, APR_BLOCK_READ, BUFFER_SIZE);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_brigade_flatten(conn->tb, conn->buffer, &bsize);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    conn->blen = bsize;
    conn->buffer[bsize] = '\0';

    return apr_brigade_cleanup(conn->tb);
}