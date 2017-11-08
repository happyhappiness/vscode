apr_status_t util_ldap_cache_init(apr_pool_t *pool, util_ldap_state_t *st)
{
#if APR_HAS_SHARED_MEMORY
    apr_status_t result;
    apr_size_t size;

    if (st->cache_bytes > 0) {
        if (st->cache_file) {
            /* Remove any existing shm segment with this name. */
            apr_shm_remove(st->cache_file, st->pool);
        }

        size = APR_ALIGN_DEFAULT(st->cache_bytes);

        result = apr_shm_create(&st->cache_shm, size, st->cache_file, st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }

        /* Determine the usable size of the shm segment. */
        size = apr_shm_size_get(st->cache_shm);

        /* This will create a rmm "handler" to get into the shared memory area */
        result = apr_rmm_init(&st->cache_rmm, NULL,
                              apr_shm_baseaddr_get(st->cache_shm), size,
                              st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }
    }

#endif

    apr_pool_cleanup_register(st->pool, st , util_ldap_cache_module_kill, apr_pool_cleanup_null);

    st->util_ldap_cache =
        util_ald_create_cache(st,
                              st->search_cache_size,
                              util_ldap_url_node_hash,
                              util_ldap_url_node_compare,
                              util_ldap_url_node_copy,
                              util_ldap_url_node_free,
                              util_ldap_url_node_display);
    return APR_SUCCESS;
}