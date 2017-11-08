apr_status_t mc_version_ping(apr_memcache_server_t *ms)
{
    apr_status_t rv;
    apr_size_t written;
    struct iovec vec[2];
    apr_memcache_conn_t *conn;

    rv = ms_find_conn(ms, &conn);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* version\r\n */
    vec[0].iov_base = MC_VERSION;
    vec[0].iov_len  = MC_VERSION_LEN;

    vec[1].iov_base = MC_EOL;
    vec[1].iov_len  = MC_EOL_LEN;

    rv = apr_socket_sendv(conn->sock, vec, 2, &written);

    if (rv != APR_SUCCESS) {
        ms_bad_conn(ms, conn);
        return rv;
    }

    rv = get_server_line(conn);
    ms_release_conn(ms, conn);
    return rv;
}