
        i++;
        posn++;
    }

    if (i != 1) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "HEADER: %s %s",
                     asc_line, hex_line);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, "HEADER: -EOH-");
#endif
}

static apr_status_t dispatch(proxy_conn_rec *conn, request_rec *r,
                             int request_id)
{
    apr_bucket_brigade *ib, *ob;
    int seen_end_of_headers = 0, done = 0;
    apr_status_t rv = APR_SUCCESS;
    conn_rec *c = r->connection;
    struct iovec vec[2];
    fcgi_header header;
    unsigned char farray[FCGI_HEADER_LEN];
    apr_pollfd_t pfd;
    int header_state = HDR_STATE_READING_HEADERS;
