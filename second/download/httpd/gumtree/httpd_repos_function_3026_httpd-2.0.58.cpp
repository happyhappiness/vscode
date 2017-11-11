apr_status_t apr_thread_data_set(void *data, const char *key,
                              apr_status_t (*cleanup) (void *),
                              apr_thread_t *thread)
{
    if (thread != NULL) {
       return apr_pool_userdata_set(data, key, cleanup, thread->pool);
    }
    else {
        data = NULL;
        return APR_ENOTHREAD;
    }
}