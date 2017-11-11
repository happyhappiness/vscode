static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t result;
    server_rec *s_vhost;
    util_ldap_state_t *st_vhost;

    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(s->module_config,
                                                 &ldap_module);

    void *data;
    const char *userdata_key = "util_ldap_init";
    apr_ldap_err_t *result_err = NULL;
    int rc;

    /* util_ldap_post_config() will be called twice. Don't bother
     * going through all of the initialization on the first call
     * because it will just be thrown away.*/
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);

#if APR_HAS_SHARED_MEMORY
        /* If the cache file already exists then delete it.  Otherwise we are
         * going to run into problems creating the shared memory. */
        if (st->cache_file) {
            char *lck_file = apr_pstrcat(ptemp, st->cache_file, ".lck",
                                         NULL);
            apr_file_remove(lck_file, ptemp);
        }
#endif
        return OK;
    }

#if APR_HAS_SHARED_MEMORY
    /* initializing cache if shared memory size is not zero and we already
     * don't have shm address
     */
    if (!st->cache_shm && st->cache_bytes > 0) {
#endif
        result = util_ldap_cache_init(p, st);
        if (result != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                         "LDAP cache: could not create shared memory segment");
            return DONE;
        }


#if APR_HAS_SHARED_MEMORY
        if (st->cache_file) {
            st->lock_file = apr_pstrcat(st->pool, st->cache_file, ".lck",
                                        NULL);
        }
#endif

        result = apr_global_mutex_create(&st->util_ldap_cache_lock,
                                         st->lock_file, APR_LOCK_DEFAULT,
                                         st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }

#ifdef AP_NEED_SET_MUTEX_PERMS
        result = unixd_set_global_mutex_perms(st->util_ldap_cache_lock);
        if (result != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, result, s,
                         "LDAP cache: failed to set mutex permissions");
            return result;
        }
#endif

        /* merge config in all vhost */
        s_vhost = s->next;
        while (s_vhost) {
            st_vhost = (util_ldap_state_t *)
                       ap_get_module_config(s_vhost->module_config,
                                            &ldap_module);

#if APR_HAS_SHARED_MEMORY
            st_vhost->cache_shm = st->cache_shm;
            st_vhost->cache_rmm = st->cache_rmm;
            st_vhost->cache_file = st->cache_file;
            st_vhost->util_ldap_cache = st->util_ldap_cache;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, result, s,
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp "
                         "for VHOST: %s", st->cache_shm, st->cache_rmm,
                         s_vhost->server_hostname);
#endif
            st_vhost->lock_file = st->lock_file;
            s_vhost = s_vhost->next;
        }
#if APR_HAS_SHARED_MEMORY
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "LDAP cache: LDAPSharedCacheSize is zero, disabling "
                     "shared memory cache");
    }
#endif

    /* log the LDAP SDK used
     */
    {
        apr_ldap_err_t *result = NULL;
        apr_ldap_info(p, &(result));
        if (result != NULL) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, "%s", result->reason);
        }
    }

    apr_pool_cleanup_register(p, s, util_ldap_cleanup_module,
                              util_ldap_cleanup_module);

    /*
     * Initialize SSL support, and log the result for the benefit of the admin.
     *
     * If SSL is not supported it is not necessarily an error, as the
     * application may not want to use it.
     */
    rc = apr_ldap_ssl_init(p,
                      NULL,
                      0,
                      &(result_err));
    if (APR_SUCCESS == rc) {
        rc = apr_ldap_set_option(ptemp, NULL, APR_LDAP_OPT_TLS_CERT,
                                 (void *)st->global_certs, &(result_err));
    }

    if (APR_SUCCESS == rc) {
        st->ssl_supported = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "LDAP: SSL support available" );
    }
    else {
        st->ssl_supported = 0;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "LDAP: SSL support unavailable%s%s",
                     result_err ? ": " : "",
                     result_err ? result_err->reason : "");
    }

    return(OK);
}