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
        mkdir_structure(conf, dobj->hdrsfile, r->pool);
    }

    rv = safe_file_rename(conf, dobj->tempfile, dobj->hdrsfile, r->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, r->server,
                     "disk_cache: rename tempfile to hdrsfile failed: %s -> %s",
                     dobj->tempfile, dobj->hdrsfile);
        apr_file_remove(dobj->tempfile, r->pool);
