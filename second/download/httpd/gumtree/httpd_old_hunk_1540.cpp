    iov[0].iov_len = sizeof(disk_cache_info_t);
    iov[1].iov_base = (void*)dobj->name;
    iov[1].iov_len = disk_info.name_len;

    rv = apr_file_writev(dobj->hfd, (const struct iovec *) &iov, 2, &amt);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (r->headers_out) {
        apr_table_t *headers_out;

        headers_out = apr_table_overlay(r->pool, r->headers_out,
                                        r->err_headers_out);
        headers_out = ap_cache_cacheable_hdrs_out(r->pool, headers_out,
                                                  r->server);

        if (!apr_table_get(headers_out, "Content-Type")
            && r->content_type) {
            apr_table_setn(headers_out, "Content-Type",
                           ap_make_content_type(r, r->content_type));
        }

        if (!apr_table_get(headers_out, "Content-Encoding")
            && r->content_encoding) {
            apr_table_setn(headers_out, "Content-Encoding",
                           r->content_encoding);
        }

        rv = store_table(dobj->hfd, headers_out);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    /* Parse the vary header and dump those fields from the headers_in. */
    /* FIXME: Make call to the same thing cache_select calls to crack Vary. */
    if (r->headers_in) {
        apr_table_t *headers_in;

        headers_in = ap_cache_cacheable_hdrs_out(r->pool, r->headers_in,
                                                 r->server);
        rv = store_table(dobj->hfd, headers_in);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    apr_file_close(dobj->hfd); /* flush and close */

    rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                     "disk_cache: rename tempfile to hdrsfile failed: %s -> %s",
                     dobj->tempfile, dobj->hdrsfile);
        apr_file_remove(dobj->tempfile, r->pool);
