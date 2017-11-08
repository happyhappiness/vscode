const char *ssl_cmd_SSLSessionCache(cmd_parms *cmd,
                                    void *dcfg,
                                    const char *arg)
{
    SSLModConfigRec *mc = myModConfig(cmd->server);
    const char *err, *sep, *name;
    long enabled_flags;

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    /* The OpenSSL session cache mode must have both the flags
     * SSL_SESS_CACHE_SERVER and SSL_SESS_CACHE_NO_INTERNAL set if a
     * session cache is configured; NO_INTERNAL prevents the
     * OpenSSL-internal session cache being used in addition to the
     * "external" (mod_ssl-provided) cache, which otherwise causes
     * additional memory consumption. */
    enabled_flags = SSL_SESS_CACHE_SERVER | SSL_SESS_CACHE_NO_INTERNAL;

    if (strcEQ(arg, "none")) {
        /* Nothing to do; session cache will be off. */
    }
    else if (strcEQ(arg, "nonenotnull")) {
        /* ### Having a separate mode for this seems logically
         * unnecessary; the stated purpose of sending non-empty
         * session IDs would be better fixed in OpenSSL or simply
         * doing it by default if "none" is used. */
        mc->sesscache_mode = enabled_flags;
    }
    else {
        /* Argument is of form 'name:args' or just 'name'. */
        sep = ap_strchr_c(arg, ':');
        if (sep) {
            name = apr_pstrmemdup(cmd->pool, arg, sep - arg);
            sep++;
        }
        else {
            name = arg;
        }

        /* Find the provider of given name. */
        mc->sesscache = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP,
                                           name,
                                           AP_SOCACHE_PROVIDER_VERSION);
        if (mc->sesscache) {
            /* Cache found; create it, passing anything beyond the colon. */
            mc->sesscache_mode = enabled_flags;
            err = mc->sesscache->create(&mc->sesscache_context, sep,
                                        cmd->temp_pool, cmd->pool);
        }
        else {
            apr_array_header_t *name_list;
            const char *all_names;

            /* Build a comma-separated list of all registered provider
             * names: */
            name_list = ap_list_provider_names(cmd->pool,
                                               AP_SOCACHE_PROVIDER_GROUP,
                                               AP_SOCACHE_PROVIDER_VERSION);
            all_names = apr_array_pstrcat(cmd->pool, name_list, ',');

            err = apr_psprintf(cmd->pool, "'%s' session cache not supported "
                               "(known names: %s). Maybe you need to load the "
                               "appropriate socache module (mod_socache_%s?).",
                               name, all_names, name);
        }
    }

    if (err) {
        return apr_psprintf(cmd->pool, "SSLSessionCache: %s", err);
    }

    return NULL;
}