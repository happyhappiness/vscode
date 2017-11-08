static apr_status_t num_cmd_write(apr_memcache_t *mc,
                                      char *cmd,
                                      const apr_uint32_t cmd_size,
                                      const char *key,
                                      const apr_int32_t inc,
                                      apr_uint32_t *new_value)
{
    apr_status_t rv;
    apr_memcache_server_t *ms;
    apr_memcache_conn_t *conn;
    apr_uint32_t hash;
    apr_size_t written;
    struct iovec vec[3];
    apr_size_t klen = strlen(key);

    hash = apr_memcache_hash(mc, key, klen);
    ms = apr_memcache_find_server_hash(mc, hash);
    if (ms == NULL)
        return APR_NOTFOUND;
    
    rv = ms_find_conn(ms, &conn);

    if (rv != APR_SUCCESS) {
        apr_memcache_disable_server(mc, ms);
        return rv;
    }

    /* <cmd> <key> <value>\r\n */
    vec[0].iov_base = cmd;
    vec[0].iov_len  = cmd_size;

    vec[1].iov_base = (void*)key;
    vec[1].iov_len  = klen;

    klen = apr_snprintf(conn->buffer, BUFFER_SIZE, " %u" MC_EOL, inc);

    vec[2].iov_base = conn->buffer;
    vec[2].iov_len  = klen;

    rv = apr_socket_sendv(conn->sock, vec, 3, &written);

    if (rv != APR_SUCCESS) {
        ms_bad_conn(ms, conn);
        apr_memcache_disable_server(mc, ms);
        return rv;
    }

    rv = get_server_line(conn);
    if (rv != APR_SUCCESS) {
        ms_bad_conn(ms, conn);
        apr_memcache_disable_server(mc, ms);
        return rv;
    }

    if (strncmp(MS_ERROR, conn->buffer, MS_ERROR_LEN) == 0) {
        rv = APR_EGENERAL;
    }
    else if (strncmp(MS_NOT_FOUND, conn->buffer, MS_NOT_FOUND_LEN) == 0) {
        rv = APR_NOTFOUND;
    }
    else {
        if (new_value) {
            *new_value = atoi(conn->buffer);
        }
        rv = APR_SUCCESS;
    }

    ms_release_conn(ms, conn);

    return rv;
}