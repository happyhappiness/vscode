void util_ald_free(const void *ptr)
{
#if APR_HAS_SHARED_MEMORY
    if (util_ldap_shm) {
        if (ptr)
            apr_rmm_free(util_ldap_rmm, apr_rmm_offset_get(util_ldap_rmm, (void *)ptr));
    } else {
        if (ptr)
            free((void *)ptr);
    }
#else
    if (ptr)
        free((void *)ptr);
#endif
}