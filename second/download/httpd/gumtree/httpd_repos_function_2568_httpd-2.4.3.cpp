static int util_ldap_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                                apr_pool_t *ptemp)
{
    apr_status_t result;

    result = ap_mutex_register(pconf, ldap_cache_mutex_type, NULL,
                               APR_LOCK_DEFAULT, 0);
    if (result != APR_SUCCESS) {
        return result;
    }

    return OK;
}