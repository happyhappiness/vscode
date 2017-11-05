static apr_status_t file_cache_el_final(disk_cache_object_t *dobj,
                                        request_rec *r)
{
    /* move the data over */
    if (dobj->tfd) {
        apr_status_t rv;

        apr_file_close(dobj->tfd);

        /* This assumes that the tempfile is on the same file system
         * as the cache_root. If not, then we need a file copy/move
         * rather than a rename.
         */
        rv = apr_file_rename(dobj->tempfile, dobj->datafile, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                         "disk_cache: rename tempfile to datafile failed:"
                         " %s -> %s", dobj->tempfile, dobj->datafile);
            apr_file_remove(dobj->tempfile, r->pool);
        }

        dobj->tfd = NULL;
    }

    return APR_SUCCESS;
}