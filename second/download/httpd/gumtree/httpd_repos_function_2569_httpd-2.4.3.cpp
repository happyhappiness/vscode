static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t result;
    server_rec *s_vhost;
    util_ldap_state_t *st_vhost;

    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(s->module_config,
                                                 &ldap_module);

    apr_ldap_err_t *result_err = NULL;
    int rc;

    /* util_ldap_post_config() will be called twice. Don't bother
     * going through all of the initialization on the first call
     * because it will just be thrown away.*/
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {

#if APR_HAS_SHARED_MEMORY
        /*
         * If we are using shared memory caching and the cache file already
         * exists then delete it.  Otherwise we are going to run into problems
         * creating the shared memory.
         */
        if (st->cache_file && st->cache_bytes > 0) {
            char *lck_file = apr_pstrcat(ptemp, st->cache_file, ".lck",
                                         NULL);
            apr_file_remove(lck_file, ptemp);
        }
#endif
        return OK;
    }

#if APR_HAS_SHARED_MEMORY
    /*
     * initializing cache if we don't already have a shm address
     */
    if (!st->cache_shm) {
#endif
        result = util_ldap_cache_init(p, st);
        if (result != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s, APLOGNO(01315)
                         "LDAP cache: could not create shared memory segment");
            return DONE;
        }

        result = ap_global_mutex_create(&st->util_ldap_cache_lock, NULL,
                                        ldap_cache_mutex_type, NULL, s, p, 0);
        if (result != APR_SUCCESS) {
            return result;
        }

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
            ap_log_error(APLOG_MARK, APLOG_DEBUG, result, s, APLOGNO(01316)
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp "
                         "for VHOST: %s", st->cache_shm, st->cache_rmm,
                         s_vhost->server_hostname);
#endif
            s_vhost = s_vhost->next;
        }
#if APR_HAS_SHARED_MEMORY
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01317)
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
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01318) "%s", result->reason);
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
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01319)
                     "LDAP: SSL support available" );
    }
    else {
        st->ssl_supported = 0;
        ap_log_error(APLOG_MARK, APLOG_INFO,