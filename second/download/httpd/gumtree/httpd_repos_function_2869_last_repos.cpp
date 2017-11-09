h2_headers *h2_headers_rcreate(request_rec *r, int status,
                                 apr_table_t *header, apr_pool_t *pool)
{
    h2_headers *headers = h2_headers_create(status, header, r->notes, pool);
    if (headers->status == HTTP_FORBIDDEN) {
        const char *cause = apr_table_get(r->notes, "ssl-renegotiate-forbidden");
        if (cause) {
            /* This request triggered a TLS renegotiation that is now allowed 
             * in HTTP/2. Tell the client that it should use HTTP/1.1 for this.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, headers->status, r,
                          APLOGNO(03061) 
                          "h2_headers(%ld): renegotiate forbidden, cause: %s",
                          (long)r->connection->id, cause);
            headers->status = H2_ERR_HTTP_1_1_REQUIRED;
        }
    }
    if (is_unsafe(r->server)) {
        apr_table_setn(headers->notes, H2_HDR_CONFORMANCE, 
                       H2_HDR_CONFORMANCE_UNSAFE);
    }
    return headers;
}