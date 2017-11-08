void util_ald_free(util_ald_cache_t *cache, const void *ptr)
{
#if APR_HAS_SHARED_MEMORY
    if (cache->rmm_addr) {
        if (ptr)
            /* Free in shared memory */
            apr_rmm_free(cache->rmm_addr, apr_rmm_offset_get(cache->rmm_addr, (void *)ptr));
    }
    else {
        if (ptr)
            /* Cache shm is not used */
            free((void *)ptr);
    }
#else
    if (ptr)
        free((void *)ptr);
#endif
}