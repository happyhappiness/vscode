 */

API_EXPORT(int) ap_setup_client_block(request_rec *r, int read_policy)
{
    const char *tenc = ap_table_get(r->headers_in, "Transfer-Encoding");
    const char *lenp = ap_table_get(r->headers_in, "Content-Length");
    unsigned long max_body;

    r->read_body = read_policy;
    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }
        if (r->read_body == REQUEST_CHUNKED_ERROR) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "chunked Transfer-Encoding forbidden: %s", r->uri);
            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        const char *pos = lenp;

        while (ap_isdigit(*pos) || ap_isspace(*pos))
            ++pos;
        if (*pos != '\0') {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "Invalid Content-Length %s", lenp);
            return HTTP_BAD_REQUEST;
        }

        r->remaining = atol(lenp);
    }

    if ((r->read_body == REQUEST_NO_BODY) &&
        (r->read_chunked || (r->remaining > 0))) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "%s with body is not allowed for %s", r->method, r->uri);
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }

    max_body = ap_get_limit_req_body(r);
    if (max_body && (r->remaining > max_body)) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
          "Request content-length of %s is larger than the configured "
          "limit of %lu", lenp, max_body);
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }

    return OK;
}

API_EXPORT(int) ap_should_client_block(request_rec *r)
{
    /* First check if we have already read the request body */
