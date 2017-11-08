static apr_status_t remove_lock(void *data)
{
    if (authn_cache_mutex) {
        apr_global_mutex_destroy(authn_cache_mutex);
        authn_cache_mutex = NULL;
    }
    return APR_SUCCESS;
}