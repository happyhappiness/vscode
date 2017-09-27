        return 1;
    }

    return 0;
}

static apr_status_t dispatch(proxy_conn_rec *conn, proxy_dir_conf *conf,
                             request_rec *r, apr_pool_t *setaside_pool,
                             apr_uint16_t request_id)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0;
    apr_status_t rv = APR_SUCCESS;
    int script_error_status = HTTP_OK;
    conn_rec *c = r->connection;
    struct iovec vec[2];
    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    apr_pollfd_t pfd;
    int header_state = HDR_STATE_READING_HEADERS;
 
    pfd.desc_type = APR_POLL_SOCKET;
    pfd.desc.s = conn->sock;
    pfd.p = r->pool;
    pfd.reqevents = APR_POLLIN | APR_POLLOUT;

    ib = apr_brigade_create(r->pool, c->bucket_alloc);
    ob = apr_brigade_create(r->pool, c->bucket_alloc);

    while (! done) {
        apr_interval_time_t timeout;
        apr_size_t len;
        int n;

        /* We need SOME kind of timeout here, or virtually anything will
         * cause timeout errors. */
        apr_socket_timeout_get(conn->sock, &timeout);

        rv = apr_poll(&pfd, 1, &n, timeout);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) {
                continue;
            }
