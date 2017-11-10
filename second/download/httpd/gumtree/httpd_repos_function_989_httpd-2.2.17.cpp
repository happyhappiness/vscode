static int remove_url(cache_handle_t *h, apr_pool_t *p)
{
    apr_status_t rc;
    disk_cache_object_t *dobj;

    /* Get disk cache object from cache handle */
    dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    if (!dobj) {
        return DECLINED;
    }

    /* Delete headers file */
    if (dobj->hdrsfile) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                     "disk_cache: Deleting %s from cache.", dobj->hdrsfile);

        rc = apr_file_remove(dobj->hdrsfile, p);
        if ((rc != APR_SUCCESS) && !APR_STATUS_IS_ENOENT(rc)) {
            /* Will only result in an output if httpd is started with -e debug.
             * For reason see log_error_core for the case s == NULL.
             */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rc, NULL,
                   "disk_cache: Failed to delete headers file %s from cache.",
                         dobj->hdrsfile);
            return DECLINED;
        }
    }

     /* Delete data file */
    if (dobj->datafile) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                     "disk_cache: Deleting %s from cache.", dobj->datafile);

        rc = apr_file_remove(dobj->datafile, p);
        if ((rc != APR_SUCCESS) && !APR_STATUS_IS_ENOENT(rc)) {
            /* Will only result in an output if httpd is started with -e debug.
             * For reason see log_error_core for the case s == NULL.
             */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rc, NULL,
                      "disk_cache: Failed to delete data file %s from cache.",
                         dobj->datafile);
            return DECLINED;
        }
    }

    /* now delete directories as far as possible up to our cache root */
    if (dobj->root) {
        const char *str_to_copy;

        str_to_copy = dobj->hdrsfile ? dobj->hdrsfile : dobj->datafile;
        if (str_to_copy) {
            char *dir, *slash, *q;

            dir = apr_pstrdup(p, str_to_copy);

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
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                              "disk_cache: Deleting directory %s from cache",
                              dir);

                 rc = apr_dir_remove(dir, p);
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