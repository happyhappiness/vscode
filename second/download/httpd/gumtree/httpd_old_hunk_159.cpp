    r->read_body = read_policy;
    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }
        if (r->read_body == REQUEST_CHUNKED_ERROR) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "chunked Transfer-Encoding forbidden: %s", r->uri);
            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        const char *pos = lenp;

        while (apr_isdigit(*pos) || apr_isspace(*pos)) {
            ++pos;
        }
        if (*pos != '\0') {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Invalid Content-Length %s", lenp);
            return HTTP_BAD_REQUEST;
        }

        r->remaining = atol(lenp);
    }

    if ((r->read_body == REQUEST_NO_BODY)
        && (r->read_chunked || (r->remaining > 0))) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "%s with body is not allowed for %s", r->method, r->uri);
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }

#ifdef AP_DEBUG
    {
