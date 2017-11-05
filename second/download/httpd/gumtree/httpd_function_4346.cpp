static OCSP_RESPONSE *read_response(apr_socket_t *sd, BIO *bio, conn_rec *c,
                                    apr_pool_t *p)
{
    apr_bucket_brigade *bb, *tmpbb;
    OCSP_RESPONSE *response;
    char *line;
    apr_size_t count;
    apr_int64_t code;

    /* Using brigades for response parsing is much simpler than using
     * apr_socket_* directly. */
    bb = apr_brigade_create(p, c->bucket_alloc);
    tmpbb = apr_brigade_create(p, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_socket_create(sd, c->bucket_alloc));

    line = get_line(tmpbb, bb, c, p);
    if (!line || strncmp(line, "HTTP/", 5)
        || (line = ap_strchr(line, ' ')) == NULL
        || (code = apr_atoi64(++line)) < 200 || code > 299) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "bad response from OCSP server: %s",
                      line ? line : "(none)");
        return NULL;
    }

    /* Read till end of headers; don't have to even bother parsing the
     * Content-Length since the server is obliged to close the
     * connection after the response anyway for HTTP/1.0. */
    count = 0;
    while ((line = get_line(tmpbb, bb, c, p)) != NULL && line[0]
           && ++count < MAX_HEADERS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "OCSP response header: %s", line);
    }

    if (count == MAX_HEADERS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "could not read response headers from OCSP server, "
                      "exceeded maximum count (%u)", MAX_HEADERS);
        return NULL;
    }
    else if (!line) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "could not read response header from OCSP server");
        return NULL;
    }

    /* Read the response body into the memory BIO. */
    count = 0;
    while (!APR_BRIGADE_EMPTY(bb)) {
        const char *data;
        apr_size_t len;
        apr_status_t rv;
        apr_bucket *e = APR_BRIGADE_FIRST(bb);

        rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
        if (rv == APR_EOF || (rv == APR_SUCCESS && len == 0)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "OCSP response: got EOF");
            break;
        }
        if (rv != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                          "error reading response from OCSP server");
            return NULL;
        }
        count += len;
        if (count > MAX_CONTENT) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                          "OCSP response size exceeds %u byte limit",
                          MAX_CONTENT);
            return NULL;
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "OCSP response: got %" APR_SIZE_T_FMT 
                      " bytes, %" APR_SIZE_T_FMT " total", len, count);

        BIO_write(bio, data, (int)len);
        apr_bucket_delete(e);
    }

    apr_brigade_destroy(bb);
    apr_brigade_destroy(tmpbb);

    /* Finally decode the OCSP response from what's stored in the
     * bio. */
    response = d2i_OCSP_RESPONSE_bio(bio, NULL);
    if (response == NULL) {
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, mySrvFromConn(c));
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "failed to decode OCSP response data");
    }

    return response;
}