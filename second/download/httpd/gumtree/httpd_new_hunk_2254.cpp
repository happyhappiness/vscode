        return -1;
#endif
#endif
    }
}

/* Dynamic lock structure */
struct CRYPTO_dynlock_value {
    apr_pool_t *pool;
    const char* file; 
    int line;
    apr_thread_mutex_t *mutex;
};

/* Global reference to the pool passed into ssl_util_thread_setup() */
apr_pool_t *dynlockpool = NULL;

/*
 * Dynamic lock creation callback
 */
static struct CRYPTO_dynlock_value *ssl_dyn_create_function(const char *file, 
                                                     int line)
{
    struct CRYPTO_dynlock_value *value;
    apr_pool_t *p;
    apr_status_t rv;

    /* 
     * We need a pool to allocate our mutex.  Since we can't clear
     * allocated memory from a pool, create a subpool that we can blow
     * away in the destruction callback. 
     */
    rv = apr_pool_create(&p, dynlockpool);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_ERR, rv, dynlockpool, 
                       "Failed to create subpool for dynamic lock");
        return NULL;
    }

    ap_log_perror(file, line, APLOG_DEBUG, 0, p, 
                  "Creating dynamic lock");
    
    value = (struct CRYPTO_dynlock_value *)apr_palloc(p, 
                                                      sizeof(struct CRYPTO_dynlock_value));
    if (!value) {
        ap_log_perror(file, line, APLOG_ERR, 0, p, 
                      "Failed to allocate dynamic lock structure");
        return NULL;
    }
    
    value->pool = p;
    /* Keep our own copy of the place from which we were created,
       using our own pool. */
    value->file = apr_pstrdup(p, file);
    value->line = line;
    rv = apr_thread_mutex_create(&(value->mutex), APR_THREAD_MUTEX_DEFAULT, 
                                p);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_ERR, rv, p, 
                      "Failed to create thread mutex for dynamic lock");
        apr_pool_destroy(p);
        return NULL;
    }
    return value;
}

/*
 * Dynamic locking and unlocking function
 */

static void ssl_dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                           const char *file, int line)
{
    apr_status_t rv;

    if (mode & CRYPTO_LOCK) {
        ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                      "Acquiring mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_lock(l->mutex);
        ap_log_perror(file, line, APLOG_DEBUG, rv, l->pool, 
                      "Mutex %s:%d acquired!", l->file, l->line);
    }
    else {
        ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                      "Releasing mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_unlock(l->mutex);
        ap_log_perror(file, line, APLOG_DEBUG, rv, l->pool, 
                      "Mutex %s:%d released!", l->file, l->line);
    }
}

/*
 * Dynamic lock destruction callback
 */
static void ssl_dyn_destroy_function(struct CRYPTO_dynlock_value *l, 
                          const char *file, int line)
{
    apr_status_t rv;

    ap_log_perror(file, line, APLOG_DEBUG, 0, l->pool, 
                  "Destroying dynamic lock %s:%d", l->file, l->line);
    rv = apr_thread_mutex_destroy(l->mutex);
    if (rv != APR_SUCCESS) {
        ap_log_perror(file, line, APLOG_ERR, rv, l->pool, 
                      "Failed to destroy mutex for dynamic lock %s:%d", 
                      l->file, l->line);
    }

    /* Trust that whomever owned the CRYPTO_dynlock_value we were
     * passed has no future use for it...
     */
    apr_pool_destroy(l->pool);
}

static unsigned long ssl_util_thr_id(void)
{
    /* OpenSSL needs this to return an unsigned long.  On OS/390, the pthread
     * id is a structure twice that big.  Use the TCB pointer instead as a
     * unique unsigned long.
     */
