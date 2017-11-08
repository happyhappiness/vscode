static apr_status_t load_ldap(apr_pool_t *pool)
{
    char *modname;
    apr_dso_handle_sym_t symbol;
    apr_status_t rv;

    /* deprecate in 2.0 - permit implicit initialization */
    apu_dso_init(pool);

    rv = apu_dso_mutex_lock();
    if (rv) {
        return rv;
    }

#if defined(WIN32)
    modname = "apr_ldap-" APU_STRINGIFY(APU_MAJOR_VERSION) ".dll";
#else
    modname = "apr_ldap-" APU_STRINGIFY(APU_MAJOR_VERSION) ".so";
#endif
    rv = apu_dso_load(&symbol, modname, "apr__ldap_fns", pool);
    if (rv == APR_SUCCESS) {
        lfn = symbol;
    }
    apu_dso_mutex_unlock();

    return rv;
}