static apr_status_t storage_cmd_write(apr_memcache_t *mc,
                                      char *cmd,
                                      const apr_size_t cmd_size,
                                      const char *key,
                                      char *data,
                                      const apr_size_t data_size,
                                      apr_uint32_t timeout,
                                      apr_uint16_t flags)
{
    apr_uint32_t hash;
    apr_memcache_server_t *ms;
    apr_memcache_conn_t *conn;
    apr_status_t rv;
    apr_size_t written;
    struct iovec vec[5];
    apr_size_t klen;

    apr_size_t key_size = strlen(key);

    hash = apr_memcache_hash(mc, key, key_size);

    ms = apr_memcache_find_server_hash(mc, hash);

    if (ms == NULL)
        return APR_NOTFOUND;

    rv = ms_find_conn(ms, &conn);

    if (rv != APR_SUCCESS) {
        apr_memcache_disable_server(mc, ms);
        return rv;
    }

    /* <command name> <key> <flags> <exptime> <bytes>\r\n<data>\r\n */

    vec[0].iov_base = cmd;
    vec[0].iov_len  = cmd_size;

    vec[1].iov_base = (void*)key;
    vec[1].iov_len  = key_size;

    klen = apr_snprintf(conn->buffer, BUFFER_SIZE, " %u %u %" APR_SIZE_T_FMT " " MC_EOL,
                        flags, timeout, data_size);

    vec[2].iov_base = conn->buffer;
    vec[2].iov_len  = klen;

    vec[3].iov_base = data;
    vec[3].iov_len  = data_size;

    vec[4].iov_base = MC_EOL;
    vec[4].iov_len  = MC_EOL_LEN;

    rv = apr_socket_sendv(conn->sock, vec, 5, &written);

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

    if (strcmp(conn->buffer, MS_STORED MC_EOL) == 0) {
        rv = APR_SUCCESS;
    }
    else if (strcmp(conn->buffer, MS_NOT_STORED MC_EOL) == 0) {
        rv = APR_EEXIST;
    }
    else {
        rv = APR_EGENERAL;
    }

    ms_release_conn(ms, conn);

    return rv;
}