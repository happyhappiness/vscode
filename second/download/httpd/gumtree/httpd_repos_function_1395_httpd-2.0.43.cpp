const char *util_ald_strdup(const char *s)
{
#if APR_HAS_SHARED_MEMORY
    if (util_ldap_shm) {
        char *buf = (char *)apr_rmm_addr_get(util_ldap_rmm, apr_rmm_calloc(util_ldap_rmm, strlen(s)+1));
        if (buf) {
            strcpy(buf, s);
            return buf;
        }
        else {
            return NULL;
        }
    } else {
        return strdup(s);
    }
#else
    return strdup(s);
#endif
}