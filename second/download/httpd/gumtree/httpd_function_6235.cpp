static apr_socket_t *send_request(BIO *request, const apr_uri_t *uri,
                                  apr_interval_time_t timeout,
                                  conn_rec *c, apr_pool_t *p)
{
    apr_status_t rv;
    apr_sockaddr_t *sa;
    apr_socket_t *sd;
    char buf[HUGE_STRING_LEN];
    int len;

    rv = apr_sockaddr_info_get(&sa, uri->hostname, APR_UNSPEC, uri->port, 0, p);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01972)
                      "could not resolve address of OCSP responder %s",
                      uri->hostinfo);
        return NULL;
    }

    /* establish a connection to the OCSP responder */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01973)
                  "connecting to OCSP responder '%s'", uri->hostinfo);

    /* Cycle through address until a connect() succeeds. */
    for (; sa; sa = sa->next) {
        rv = apr_socket_create(&sd, sa->family, SOCK_STREAM, APR_PROTO_TCP, p);
        if (rv == APR_SUCCESS) {
            apr_socket_timeout_set(sd, timeout);

            rv = apr_socket_connect(sd, sa);
            if (rv == APR_SUCCESS) {
                break;
            }
            apr_socket_close(sd);
        }
    }

    if (sa == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01974)
                      "could not connect to OCSP responder '%s'",
                      uri->hostinfo);
        return NULL;
    }

    /* send the request and get a response */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01975)
                 "sending request to OCSP responder");

    while ((len = BIO_read(request, buf, sizeof buf)) > 0) {
        char *wbuf = buf;
        apr_size_t remain = len;

        do {
            apr_size_t wlen = remain;

            rv = apr_socket_send(sd, wbuf, &wlen);
            wbuf += remain;
            remain -= wlen;
        } while (rv == APR_SUCCESS && remain > 0);

        if (rv) {
            apr_socket_close(sd);
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01976)
                          "failed to send request to OCSP responder '%s'",
                          uri->hostinfo);
            return NULL;
        }
    }

    return sd;
}