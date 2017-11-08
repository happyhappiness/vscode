apr_status_t apr_thread_data_get(void **data, const char *key,
                                             apr_thread_t *thread)
{
    if (thread != NULL) {
            return apr_pool_userdata_get(data, key, thread->pool);
    }
    else {
        data = NULL;
        return APR_ENOTHREAD;
    }
}