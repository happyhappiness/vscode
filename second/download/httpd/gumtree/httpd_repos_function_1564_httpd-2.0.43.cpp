apr_status_t util_ldap_cache_module_kill(void *data)
{
#if APR_HAS_SHARED_MEMORY
    if (util_ldap_shm != NULL) {
        apr_status_t result = apr_shm_destroy(util_ldap_shm);
        util_ldap_shm = NULL;
        return result;
    }
#endif
    util_ald_destroy_cache(util_ldap_cache);
    return APR_SUCCESS;
}