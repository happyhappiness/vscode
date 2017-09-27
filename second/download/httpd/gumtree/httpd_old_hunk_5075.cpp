        return 1;
    }

    return 0;
}

static void dump_header_to_log(request_rec *r, unsigned char fheader[],
                               apr_size_t length)
{
#ifdef FCGI_DUMP_HEADERS
    apr_size_t posn = 0;
    char asc_line[20];
    char hex_line[60];
    int i = 0;

    memset(asc_line, 0, sizeof(asc_line));
    memset(hex_line, 0, sizeof(hex_line));

    while (posn < length) {
        unsigned char c = fheader[posn];

        if (i >= 20) {
            i = 0;

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01064)
                          "HEADER: %s %s", asc_line, hex_line);

            memset(asc_line, 0, sizeof(asc_line));
            memset(hex_line, 0, sizeof(hex_line));
        }

        if (isprint(c)) {
            asc_line[i] = c;
        }
        else {
            asc_line[i] = '.';
        }

        if ((c >> 4) >= 10) {
            hex_line[i * 3] = 'a' + ((c >> 4) - 10);
        }
        else {
            hex_line[i * 3] = '0' + (c >> 4);
        }

        if ((c & 0x0F) >= 10) {
            hex_line[i * 3 + 1] = 'a' + ((c & 0x0F) - 10);
        }
        else {
            hex_line[i * 3 + 1] = '0' + (c & 0xF);
        }

        hex_line[i * 3 + 2] = ' ';

        i++;
        posn++;
    }

    if (i != 1) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01065) "HEADER: %s %s",
                      asc_line, hex_line);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01066) "HEADER: -EOH-");
#endif
}

static apr_status_t dispatch(proxy_conn_rec *conn, proxy_dir_conf *conf,
                             request_rec *r, int request_id)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0;
    apr_status_t rv = APR_SUCCESS;
    int script_error_status = HTTP_OK;
    conn_rec *c = r->connection;
    struct iovec vec[2];
    fcgi_header header;
    unsigned char farray[FCGI_HEADER_LEN];
    apr_pollfd_t pfd;
    int header_state = HDR_STATE_READING_HEADERS;
    apr_pool_t *setaside_pool;

    apr_pool_create(&setaside_pool, r->pool);

    pfd.desc_type = APR_POLL_SOCKET;
    pfd.desc.s = conn->sock;
    pfd.p = r->pool;
    pfd.reqevents = APR_POLLIN | APR_POLLOUT;

    ib = apr_brigade_create(r->pool, c->bucket_alloc);
    ob = apr_brigade_create(r->pool, c->bucket_alloc);

    while (! done) {
        apr_interval_time_t timeout = conn->worker->s->timeout;
        apr_size_t len;
        int n;

        /* We need SOME kind of timeout here, or virtually anything will
         * cause timeout errors. */
        if (! conn->worker->s->timeout_set) {
            timeout = apr_time_from_sec(30);
        }

        rv = apr_poll(&pfd, 1, &n, timeout);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) {
                continue;
            }
