    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_socket_create(sd, c->bucket_alloc));

    line = get_line(tmpbb, bb, c, p);
    if (!line || strncmp(line, "HTTP/", 5)
        || (line = ap_strchr(line, ' ')) == NULL
        || (code = apr_atoi64(++line)) < 200 || code > 299) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01980)
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
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01981)
                      "OCSP response header: %s", line);
    }

    if (count == MAX_HEADERS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01982)
                      "could not read response headers from OCSP server, "
                      "exceeded maximum count (%u)", MAX_HEADERS);
        return NULL;
    }
    else if (!line) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01983)
                      "could not read response header from OCSP server");
        return NULL;
    }

    /* Read the response body into the memory BIO. */
    count = 0;
