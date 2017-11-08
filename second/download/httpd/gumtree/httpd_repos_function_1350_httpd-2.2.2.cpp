static void basic_http_header(request_rec *r, apr_bucket_brigade *bb,
                              const char *protocol)
{
    char *date;
    const char *server;
    header_struct h;
    struct iovec vec[4];

    if (r->assbackwards) {
        /* there are no headers to send */
        return;
    }

    /* Output the HTTP/1.x Status-Line and the Date and Server fields */

    vec[0].iov_base = (void *)protocol;
    vec[0].iov_len  = strlen(protocol);
    vec[1].iov_base = (void *)" ";
    vec[1].iov_len  = sizeof(" ") - 1;
    vec[2].iov_base = (void *)(r->status_line);
    vec[2].iov_len  = strlen(r->status_line);
    vec[3].iov_base = (void *)CRLF;
    vec[3].iov_len  = sizeof(CRLF) - 1;
#if APR_CHARSET_EBCDIC
    {
        char *tmp;
        apr_size_t len;
        tmp = apr_pstrcatv(r->pool, vec, 4, &len);
        ap_xlate_proto_to_ascii(tmp, len);
        apr_brigade_write(bb, NULL, NULL, tmp, len);
    }
#else
    apr_brigade_writev(bb, NULL, NULL, vec, 4);
#endif

    date = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
    ap_recent_rfc822_date(date, r->request_time);

    h.pool = r->pool;
    h.bb = bb;
    form_header_field(&h, "Date", date);

    /* keep the set-by-proxy server header, otherwise
     * generate a new server header */
    if (r->proxyreq != PROXYREQ_NONE) {
        server = apr_table_get(r->headers_out, "Server");
        if (server) {
            form_header_field(&h, "Server", server);
        }
    }
    else {
        form_header_field(&h, "Server", ap_get_server_version());
    }

    /* unset so we don't send them again */
    apr_table_unset(r->headers_out, "Date");        /* Avoid bogosity */
    apr_table_unset(r->headers_out, "Server");
}