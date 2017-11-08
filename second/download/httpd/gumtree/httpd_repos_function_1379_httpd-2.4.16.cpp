void cache_accept_headers(cache_handle_t *h, request_rec *r, apr_table_t *top,
        apr_table_t *bottom, int revalidation)
{
    const char *v;

    if (revalidation) {
        r->headers_out = apr_table_make(r->pool, 10);
        apr_table_do(filter_header_do, r->headers_out, bottom, NULL);
    }
    else if (r->headers_out != bottom) {
        r->headers_out = apr_table_copy(r->pool, bottom);
    }
    apr_table_do(remove_header_do, r->headers_out, top, NULL);
    apr_table_do(add_header_do, r->headers_out, top, NULL);

    v = apr_table_get(r->headers_out, "Content-Type");
    if (v) {
        ap_set_content_type(r, v);
        /*
         * Also unset possible Content-Type headers in r->headers_out and
         * r->err_headers_out as they may be different to what we have received
         * from the cache.
         * Actually they are not needed as r->content_type set by
         * ap_set_content_type above will be used in the store_headers functions
         * of the storage providers as a fallback and the HTTP_HEADER filter
         * does overwrite the Content-Type header with r->content_type anyway.
         */
        apr_table_unset(r->headers_out, "Content-Type");
        apr_table_unset(r->err_headers_out, "Content-Type");
    }

    /* If the cache gave us a Last-Modified header, we can't just
     * pass it on blindly because of restrictions on future values.
     */
    v = apr_table_get(r->headers_out, "Last-Modified");
    if (v) {
        ap_update_mtime(r, apr_date_parse_http(v));
        ap_set_last_modified(r);
    }

}