void ssl_dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                           const char *file, int line)
{
    apr_status_t rv;

    if (mode & CRYPTO_LOCK) {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, 0, l->pool,
                      "Acquiring mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_lock(l->mutex);
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, rv, l->pool,
                      "Mutex %s:%d acquired!", l->file, l->line);
    }
    else {
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, 0, l->pool,
                      "Releasing mutex %s:%d", l->file, l->line);
        rv = apr_thread_mutex_unlock(l->mutex);
        ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, rv, l->pool,
                      "Mutex %s:%d released!", l->file, l->line);
    }
}