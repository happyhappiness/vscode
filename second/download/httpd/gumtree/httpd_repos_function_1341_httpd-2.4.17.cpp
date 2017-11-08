static apr_status_t remove_lock(void *data)
{
    if (socache_mutex) {
        apr_global_mutex_destroy(socache_mutex);
        socache_mutex = NULL;
    }
    return APR_SUCCESS;
}