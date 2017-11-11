static int process_mkcol_body(request_rec *r)
{
    /* This is snarfed from ap_setup_client_block(). We could get pretty
     * close to this behavior by passing REQUEST_NO_BODY, but we need to
     * return HTTP_UNSUPPORTED_MEDIA_TYPE (while ap_setup_client_block
     * returns HTTP_REQUEST_ENTITY_TOO_LARGE). */

    const char *tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
    const char *lenp = apr_table_get(r->headers_in, "Content-Length");

    /* make sure to set the Apache request fields properly. */
    r->read_body = REQUEST_NO_BODY;
    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            /* Use this instead of Apache's default error string */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        const char *pos = lenp;

        while (apr_isdigit(*pos) || apr_isspace(*pos)) {
            ++pos;
        }

        if (*pos != '\0') {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid Content-Length %s", lenp);
            return HTTP_BAD_REQUEST;
        }

        r->remaining = apr_atoi64(lenp);
    }

    if (r->read_chunked || r->remaining > 0) {
        /* ### log something? */

        /* Apache will supply a default error for this. */
        return HTTP_UNSUPPORTED_MEDIA_TYPE;
    }

    /*
     * Get rid of the body. this will call ap_setup_client_block(), but
     * our copy above has already verified its work.
     */
    return ap_discard_request_body(r);
}