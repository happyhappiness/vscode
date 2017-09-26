        return APR_SUCCESS;
    }
    return get_remaining_chunk_line(ctx, b, linelimit);
}


/* This is the HTTP_INPUT filter for HTTP requests and responses from
 * proxied servers (mod_proxy).  It handles chunked and content-length
 * bodies.  This can only be inserted/used after the headers
 * are successfully parsed.
 */
apr_status_t ap_http_filter(ap_filter_t *f, apr_bucket_brigade *b,
                            ap_input_mode_t mode, apr_read_type_e block,
                            apr_off_t readbytes)
{
    apr_bucket *e;
    http_ctx_t *ctx = f->ctx;
    apr_status_t rv;
    apr_off_t totalread;
    int http_error = HTTP_REQUEST_ENTITY_TOO_LARGE;
    apr_bucket_brigade *bb;

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
        return ap_get_brigade(f->next, b, mode, block, readbytes);
    }

    if (!ctx) {
