static apr_status_t proc_mutex_fcntl_create(apr_proc_mutex_t *new_mutex,
                                            const char *fname)
{
    int rv;
 
    if (fname) {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, fname);
        rv = apr_file_open(&new_mutex->interproc, new_mutex->fname,
                           APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_EXCL,
                           APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD,
                           new_mutex->pool);
    }
    else {
        new_mutex->fname = apr_pstrdup(new_mutex->pool, "/tmp/aprXXXXXX");
        rv = apr_file_mktemp(&new_mutex->interproc, new_mutex->fname,
                             APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_EXCL,
                             new_mutex->pool);
    }
 
    if (rv != APR_SUCCESS) {
        return rv;
    }

    new_mutex->curr_locked = 0;
    unlink(new_mutex->fname);
    apr_pool_cleanup_register(new_mutex->pool,
                              (void*)new_mutex,
                              apr_proc_mutex_cleanup, 
                              apr_pool_cleanup_null);
    return APR_SUCCESS; 
}