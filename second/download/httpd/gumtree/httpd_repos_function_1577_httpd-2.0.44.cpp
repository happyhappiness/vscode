apr_status_t util_ldap_cache_init(apr_pool_t *pool, apr_size_t reqsize)
{
#if APR_HAS_SHARED_MEMORY
    apr_status_t result;

    result = apr_shm_create(&util_ldap_shm, reqsize, "/tmp/ldap_cache", pool);
    if (result != APR_SUCCESS) {
        return result;
    }

    /* This will create a rmm "handler" to get into the shared memory area */
    apr_rmm_init(&util_ldap_rmm, NULL,
			(void *)apr_shm_baseaddr_get(util_ldap_shm), reqsize, pool);
#endif

    apr_pool_cleanup_register(pool, NULL, util_ldap_cache_module_kill, apr_pool_cleanup_null);

    util_ldap_cache = util_ald_create_cache(50,
				     util_ldap_url_node_hash,
				     util_ldap_url_node_compare,
				     util_ldap_url_node_copy,
				     util_ldap_url_node_free);
    return APR_SUCCESS;
}