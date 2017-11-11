static apr_status_t dbm_open_type(apr_dbm_type_t const* * vtable,
                                  const char *type, 
                                  apr_pool_t *pool)
{
#if !APU_DSO_BUILD

    *vtable = NULL;
    if (!strcasecmp(type, "default"))     *vtable = &DBM_VTABLE;
#if APU_HAVE_DB
    else if (!strcasecmp(type, "db"))     *vtable = &apr_dbm_type_db;
#endif
    else if (*type && !strcasecmp(type + 1, "dbm")) {
#if APU_HAVE_GDBM
        if (*type == 'G' || *type == 'g') *vtable = &apr_dbm_type_gdbm;
#endif
#if APU_HAVE_NDBM
        if (*type == 'N' || *type == 'n') *vtable = &apr_dbm_type_ndbm;
#endif
#if APU_HAVE_SDBM
        if (*type == 'S' || *type == 's') *vtable = &apr_dbm_type_sdbm;
#endif
        /* avoid empty block */ ;
    }
    if (*vtable)
        return APR_SUCCESS;
    return APR_ENOTIMPL;

#else /* APU_DSO_BUILD */

    char modname[32];
    char symname[34];
    apr_dso_handle_sym_t symbol;
    apr_status_t rv;
    int usertype = 0;

    if (!strcasecmp(type, "default"))        type = DBM_NAME;
    else if (!strcasecmp(type, "db"))        type = "db";
    else if (*type && !strcasecmp(type + 1, "dbm")) {
        if      (*type == 'G' || *type == 'g') type = "gdbm"; 
        else if (*type == 'N' || *type == 'n') type = "ndbm"; 
        else if (*type == 'S' || *type == 's') type = "sdbm"; 
    }
    else usertype = 1;

    if (apr_atomic_inc32(&initialised)) {
        apr_atomic_set32(&initialised, 1); /* prevent wrap-around */

        while (apr_atomic_read32(&in_init)) /* wait until we get fully inited */
            ;
    }
    else {
        apr_pool_t *parent;

        /* Top level pool scope, need process-scope lifetime */
        for (parent = pool;  parent; parent = apr_pool_parent_get(pool))
             pool = parent;

        /* deprecate in 2.0 - permit implicit initialization */
        apu_dso_init(pool);

        drivers = apr_hash_make(pool);
        apr_hash_set(drivers, "sdbm", APR_HASH_KEY_STRING, &apr_dbm_type_sdbm);

        apr_pool_cleanup_register(pool, NULL, dbm_term,
                                  apr_pool_cleanup_null);

        apr_atomic_dec32(&in_init);
    }

    rv = apu_dso_mutex_lock();
    if (rv) {
        *vtable = NULL;
        return rv;
    }

    *vtable = apr_hash_get(drivers, type, APR_HASH_KEY_STRING);
    if (*vtable) {
        apu_dso_mutex_unlock();
        return APR_SUCCESS;
    }

    /* The driver DSO must have exactly the same lifetime as the
     * drivers hash table; ignore the passed-in pool */
    pool = apr_hash_pool_get(drivers);

#if defined(NETWARE)
    apr_snprintf(modname, sizeof(modname), "dbm%s.nlm", type);
#elif defined(WIN32)
    apr_snprintf(modname, sizeof(modname),
                 "apr_dbm_%s-" APU_STRINGIFY(APU_MAJOR_VERSION) ".dll", type);
#else
    apr_snprintf(modname, sizeof(modname),
                 "apr_dbm_%s-" APU_STRINGIFY(APU_MAJOR_VERSION) ".so", type);
#endif
    apr_snprintf(symname, sizeof(symname), "apr_dbm_type_%s", type);

    rv = apu_dso_load(NULL, &symbol, modname, symname, pool);
    if (rv == APR_SUCCESS || rv == APR_EINIT) { /* previously loaded?!? */
        *vtable = symbol;
        if (usertype)
            type = apr_pstrdup(pool, type);
        apr_hash_set(drivers, type, APR_HASH_KEY_STRING, *vtable);
        rv = APR_SUCCESS;
    }
    else
        *vtable = NULL;

    apu_dso_mutex_unlock();
    return rv;

#endif /* APU_DSO_BUILD */
}