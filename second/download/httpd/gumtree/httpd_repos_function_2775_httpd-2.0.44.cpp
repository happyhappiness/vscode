static apr_status_t proc_mutex_fcntl_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    int rv;
 
    if (fname) {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, fname);
        rv = apr_file_open(&new_mutex->interproc, new_mutex->fname,
                           APR_CREATE | APR_WRITE | APR_EXCL, 
                           APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD,
                           new_mutex->pool);
    }
    else {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, "/tmp/aprXXXXXX");
        rv = apr_file_mktemp(&new_mutex->interproc, new_mutex->fname, 0,
                             new_mutex->pool);
    }
 
    if (rv != APR_SUCCESS) {
        proc_mutex_fcntl_cleanup(new_mutex);
        return rv;
    }

    new_mutex->curr_locked = 0;
    /* XXX currently, apr_file_mktemp() always specifies that the file should
     *     be removed when closed; that unlink() will fail since we're 
     *     removing it here; we want to remove it here since we don't need
     *     it visible and we want it cleaned up if we exit catastrophically
     */
    unlink(new_mutex->fname);
    apr_pool_cleanup_register(new_mutex->pool,
                              (void*)new_mutex,
                              apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS; 
}