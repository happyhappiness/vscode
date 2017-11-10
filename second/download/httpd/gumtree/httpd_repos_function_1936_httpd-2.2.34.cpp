static apr_status_t util_ldap_cache_module_kill(void *data)
{
    util_ldap_state_t *st = data;

    util_ald_destroy_cache(st->util_ldap_cache);
#if APR_HAS_SHARED_MEMORY
    if (st->cache_rmm != NULL) {
        apr_rmm_destroy (st->cache_rmm);
        st->cache_rmm = NULL;
    }
    if (st->cache_shm != NULL) {
        apr_status_t result = apr_shm_destroy(st->cache_shm);
        st->cache_shm = NULL;
        return result;
    }
#endif
    return APR_SUCCESS;
}