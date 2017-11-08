static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
                                apr_file_t *fpout, char *key)
{
    char buf[LONG_STRING_LEN];
    char c;
    int i;
    apr_size_t nbytes;
    apr_status_t rv;

#ifndef NO_WRITEV
    struct iovec iova[2];
    apr_size_t niov;
#endif

    /* when `RewriteEngine off' was used in the per-server
     * context then the rewritemap-programs were not spawned.
     * In this case using such a map (usually in per-dir context)
     * is useless because it is not available.
     */
    if (fpin == NULL || fpout == NULL) {
        return NULL;
    }

    /* take the lock */

    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }

    /* write out the request key */
#ifdef NO_WRITEV
    nbytes = strlen(key);
    apr_file_write(fpin, key, &nbytes);
    nbytes = 1;
    apr_file_write(fpin, "\n", &nbytes);
#else
    iova[0].iov_base = key;
    iova[0].iov_len = strlen(key);
    iova[1].iov_base = "\n";
    iova[1].iov_len = 1;

    niov = 2;
    apr_file_writev(fpin, iova, niov, &nbytes);
#endif

    /* read in the response value */
    i = 0;
    nbytes = 1;
    apr_file_read(fpout, &c, &nbytes);
    while (nbytes == 1 && (i < LONG_STRING_LEN-1)) {
        if (c == '\n') {
            break;
        }
        buf[i++] = c;

        apr_file_read(fpout, &c, &nbytes);
    }
    buf[i] = '\0';

    /* give the lock back */
    if (rewrite_mapr_lock_acquire) {
        rv = apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
                          "failed");
            return NULL; /* Maybe this should be fatal? */
        }
    }

    if (strcasecmp(buf, "NULL") == 0) {
        return NULL;
    }
    else {
        return apr_pstrdup(r->pool, buf);
    }
}