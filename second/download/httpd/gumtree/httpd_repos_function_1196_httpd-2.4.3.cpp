void cache_accept_headers(cache_handle_t *h, request_rec *r,
        int preserve_orig)
{
    apr_table_t *cookie_table, *hdr_copy;
    const char *v;

    v = apr_table_get(h->resp_hdrs, "Content-Type");
    if (v) {
        ap_set_content_type(r, v);
        apr_table_unset(h->resp_hdrs, "Content-Type");
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
    v = apr_table_get(h->resp_hdrs, "Last-Modified");
    if (v) {
        ap_update_mtime(r, apr_date_parse_http(v));
        ap_set_last_modified(r);
        apr_table_unset(h->resp_hdrs, "Last-Modified");
    }

    /* The HTTP specification says that it is legal to merge duplicate
     * headers into one.  Some browsers that support Cookies don't like
     * merged headers and prefer that each Set-Cookie header is sent
     * separately.  Lets humour those browsers by not merging.
     * Oh what a pain it is.
     */
    cookie_table = apr_table_make(r->pool, 2);
    apr_table_do(set_cookie_doo_doo, cookie_table, r->err_headers_out,
                 "Set-Cookie", NULL);
    apr_table_do(set_cookie_doo_doo, cookie_table, h->resp_hdrs,
                 "Set-Cookie", NULL);
    apr_table_unset(r->err_headers_out, "Set-Cookie");
    apr_table_unset(h->resp_hdrs, "Set-Cookie");

    if (preserve_orig) {
        hdr_copy = apr_table_copy(r->pool, h->resp_hdrs);
        apr_table_overlap(hdr_copy, r->headers_out, APR_OVERLAP_TABLES_SET);
        r->headers_out = hdr_copy;
    }
    else {
        apr_table_overlap(r->headers_out, h->resp_hdrs, APR_OVERLAP_TABLES_SET);
    }
    if (!apr_is_empty_table(cookie_table)) {
        r->err_headers_out = apr_table_overlay(r->pool, r->err_headers_out,
                                               cookie_table);
    }
}