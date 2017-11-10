const char *util_ald_strdup(util_ald_cache_t *cache, const char *s)
{
#if APR_HAS_SHARED_MEMORY
    if (cache->rmm_addr) {
        /* allocate from shared memory */
        apr_rmm_off_t block = apr_rmm_calloc(cache->rmm_addr, strlen(s)+1);
        char *buf = block ? (char *)apr_rmm_addr_get(cache->rmm_addr, block) : NULL;
        if (buf) {
            strcpy(buf, s);
            return buf;
        }
        else {
            return NULL;
        }
    } else {
        /* Cache shm is not used */
        return strdup(s);
    }
#else
    return strdup(s);
#endif
}