static apr_status_t global_mutex_cleanup(void *data)
{
    apr_global_mutex_t *m = (apr_global_mutex_t *)data;
    apr_status_t rv;

    rv = apr_proc_mutex_destroy(m->proc_mutex);

#if APR_HAS_THREADS
    if (m->thread_mutex) {
        if (rv != APR_SUCCESS) {
            (void)apr_thread_mutex_destroy(m->thread_mutex);
        }
        else {
            rv = apr_thread_mutex_destroy(m->thread_mutex);
        }
    }
#endif /* APR_HAS_THREADS */

    return rv;
}