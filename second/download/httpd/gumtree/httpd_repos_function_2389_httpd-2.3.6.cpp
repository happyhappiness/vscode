void *util_ald_alloc(util_ald_cache_t *cache, unsigned long size)
{
    if (0 == size)
        return NULL;
#if APR_HAS_SHARED_MEMORY
    if (cache->rmm_addr) {
        /* allocate from shared memory */
        apr_rmm_off_t block = apr_rmm_calloc(cache->rmm_addr, size);
        return block ? (void *)apr_rmm_addr_get(cache->rmm_addr, block) : NULL;
    }
    else {
        /* Cache shm is not used */
        return (void *)calloc(sizeof(char), size);
    }
#else
    return (void *)calloc(sizeof(char), size);
#endif
}