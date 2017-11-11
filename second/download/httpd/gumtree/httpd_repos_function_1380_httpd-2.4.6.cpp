static int remove_url(cache_handle_t *h, request_rec *r)
{
    apr_status_t rc;
    disk_cache_object_t *dobj;

    /* Get disk cache object from cache handle */
    dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    if (!dobj) {
        return DECLINED;
    }

    /* Delete headers file */
    if (dobj->hdrs.file) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00711)
                "Deleting %s from cache.", dobj->hdrs.file);

        rc = apr_file_remove(dobj->hdrs.file, r->pool);
        if ((rc != APR_SUCCESS) && !APR_STATUS_IS_ENOENT(rc)) {
            /* Will only result in an output if httpd is started with -e debug.
             * For reason see log_error_core for the case s == NULL.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(00712)
                    "Failed to delete headers file %s from cache.",
                    dobj->hdrs.file);
            return DECLINED;
        }
    }

    /* Delete data file */
    if (dobj->data.file) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00713)
                "Deleting %s from cache.", dobj->data.file);

        rc = apr_file_remove(dobj->data.file, r->pool);
        if ((rc != APR_SUCCESS) && !APR_STATUS_IS_ENOENT(rc)) {
            /* Will only result in an output if httpd is started with -e debug.
             * For reason see log_error_core for the case s == NULL.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(00714)
                    "Failed to delete data file %s from cache.",
                    dobj->data.file);
            return DECLINED;
        }
    }

    /* now delete directories as far as possible up to our cache root */
    if (dobj->root) {
        const char *str_to_copy;

        str_to_copy = dobj->hdrs.file ? dobj->hdrs.file : dobj->data.file;
        if (str_to_copy) {
            char *dir, *slash, *q;

            dir = apr_pstrdup(r->pool, str_to_copy);

            /* remove filename */
            slash = strrchr(dir, '/');
            *slash = '\0';

            /*
             * now walk our way back to the cache root, delete everything
             * in the way as far as possible
             *
             * Note: due to the way we constructed the file names in
             * header_file and data_file, we are guaranteed that the
             * cache_root is suffixed by at least one '/' which will be
             * turned into a terminating null by this loop.  Therefore,
             * we won't either delete or go above our cache root.
             */
            for (q = dir + dobj->root_len; *q ; ) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00715)
                        "Deleting directory %s from cache", dir);

                 rc = apr_dir_remove(dir, r->pool);
                 if (rc != APR_SUCCESS && !APR_STATUS_IS_ENOENT(rc)) {
                    break;
                 }
                 slash = strrchr(q, '/');
                 *slash = '\0';
            }
        }
    }

    return OK;
}