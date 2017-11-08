void *util_ald_alloc(unsigned long size)
{
    if (0 == size)
        return NULL;
#if APR_HAS_SHARED_MEMORY
    if (util_ldap_shm) {
        return (void *)apr_rmm_addr_get(util_ldap_rmm, apr_rmm_calloc(util_ldap_rmm, size));
    } else {
        return (void *)calloc(sizeof(char), size);
    }
#else
    return (void *)calloc(sizeof(char), size);
#endif
}