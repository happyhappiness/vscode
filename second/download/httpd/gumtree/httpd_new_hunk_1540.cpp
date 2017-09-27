    iov[0].iov_len = sizeof(disk_cache_info_t);
    iov[1].iov_base = (void*)dobj->name;
    iov[1].iov_len = disk_info.name_len;

    rv = apr_file_writev(dobj->hfd, (const struct iovec *) &iov, 2, &amt);
    if (rv != APR_SUCCESS) {
       ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
           "disk_cache: could not write info to header file %s",
           dobj->hdrsfile);
        return rv;
    }

    if (r->headers_out) {
        apr_table_t *headers_out;

        headers_out = ap_cache_cacheable_headers_out(r);

        rv = store_table(dobj->hfd, headers_out);
        if (rv != APR_SUCCESS) {
           ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
               "disk_cache: could not write out-headers to header file %s",
               dobj->hdrsfile);
            return rv;
        }
    }

    /* Parse the vary header and dump those fields from the headers_in. */
    /* FIXME: Make call to the same thing cache_select calls to crack Vary. */
    if (r->headers_in) {
        apr_table_t *headers_in;

        headers_in = ap_cache_cacheable_headers_in(r);

        rv = store_table(dobj->hfd, headers_in);
        if (rv != APR_SUCCESS) {
           ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
               "disk_cache: could not write in-headers to header file %s",
               dobj->hdrsfile);
            return rv;
        }
    }

    apr_file_close(dobj->hfd); /* flush and close */

    /* Remove old file with the same name. If remove fails, then
     * perhaps we need to create the directory tree where we are
     * about to write the new headers file.
     */
    rv = apr_file_remove(dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        rv = mkdir_structure(conf, dobj->hdrsfile, r->pool);
    }

    rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                     "disk_cache: rename tempfile to hdrsfile failed: %s -> %s",
                     dobj->tempfile, dobj->hdrsfile);
        apr_file_remove(dobj->tempfile, r->pool);
