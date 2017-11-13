static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, 
                                 apr_pool_t *ptemp, server_rec *s)
{
    int rc = LDAP_SUCCESS;
    apr_status_t result;
    char buf[MAX_STRING_LEN];
    server_rec *s_vhost;
    util_ldap_state_t *st_vhost;

    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(s->module_config, &ldap_module);

    void *data;
    const char *userdata_key = "util_ldap_init";
    struct timeval timeOut = {10,0};    /* 10 second connection timeout */

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
            char *lck_file = apr_pstrcat (st->pool, st->cache_file, ".lck", NULL);
            apr_file_remove(st->cache_file, ptemp);
            apr_file_remove(lck_file, ptemp);
        }
#endif
        return OK;
    }

#if APR_HAS_SHARED_MEMORY
    /* initializing cache if shared memory size is not zero and we already don't have shm address */
    if (!st->cache_shm && st->cache_bytes > 0) {
#endif
        result = util_ldap_cache_init(p, st);
        if (result != APR_SUCCESS) {
            apr_strerror(result, buf, sizeof(buf));
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                         "LDAP cache: error while creating a shared memory segment: %s", buf);
        }


#if APR_HAS_SHARED_MEMORY
        if (st->cache_file) {
            st->lock_file = apr_pstrcat (st->pool, st->cache_file, ".lck", NULL);
        }
        else
#endif
            st->lock_file = ap_server_root_relative(st->pool, tmpnam(NULL));

        result = apr_global_mutex_create(&st->util_ldap_cache_lock, st->lock_file, APR_LOCK_DEFAULT, st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }

        /* merge config in all vhost */
        s_vhost = s->next;
        while (s_vhost) {
            st_vhost = (util_ldap_state_t *)ap_get_module_config(s_vhost->module_config, &ldap_module);

#if APR_HAS_SHARED_MEMORY
            st_vhost->cache_shm = st->cache_shm;
            st_vhost->cache_rmm = st->cache_rmm;
            st_vhost->cache_file = st->cache_file;
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp for VHOST: %s",
                         st->cache_shm, st->cache_rmm, s_vhost->server_hostname);
#endif
            st_vhost->lock_file = st->lock_file;
            s_vhost = s_vhost->next;
        }
#if APR_HAS_SHARED_MEMORY
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "LDAP cache: LDAPSharedCacheSize is zero, disabling shared memory cache");
    }
#endif
    
    /* log the LDAP SDK used 
     */
    #if APR_HAS_NETSCAPE_LDAPSDK 
    
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with Netscape LDAP SDK" );

    #elif APR_HAS_NOVELL_LDAPSDK

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with Novell LDAP SDK" );

    #elif APR_HAS_OPENLDAP_LDAPSDK

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with OpenLDAP LDAP SDK" );

    #elif APR_HAS_MICROSOFT_LDAPSDK
    
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with Microsoft LDAP SDK" );
    #else
    
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
             "LDAP: Built with unknown LDAP SDK" );

    #endif /* APR_HAS_NETSCAPE_LDAPSDK */



    apr_pool_cleanup_register(p, s, util_ldap_cleanup_module,
                              util_ldap_cleanup_module); 

    /* initialize SSL support if requested
    */
    if (st->cert_auth_file)
    {
        #if APR_HAS_LDAP_SSL /* compiled with ssl support */

        #if APR_HAS_NETSCAPE_LDAPSDK 

            /* Netscape sdk only supports a cert7.db file 
            */
            if (st->cert_file_type == LDAP_CA_TYPE_CERT7_DB)
            {
                rc = ldapssl_client_init(st->cert_auth_file, NULL);
            }
            else
            {
                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
                         "LDAP: Invalid LDAPTrustedCAType directive - "
                          "CERT7_DB_PATH type required");
                rc = -1;
            }

        #elif APR_HAS_NOVELL_LDAPSDK
        
            /* Novell SDK supports DER or BASE64 files
            */
            if (st->cert_file_type == LDAP_CA_TYPE_DER  ||
                st->cert_file_type == LDAP_CA_TYPE_BASE64 )
            {
                rc = ldapssl_client_init(NULL, NULL);
                if (LDAP_SUCCESS == rc)
                {
                    if (st->cert_file_type == LDAP_CA_TYPE_BASE64)
                        rc = ldapssl_add_trusted_cert(st->cert_auth_file, 
                                                  LDAPSSL_CERT_FILETYPE_B64);
                    else
                        rc = ldapssl_add_trusted_cert(st->cert_auth_file, 
                                                  LDAPSSL_CERT_FILETYPE_DER);

                    if (LDAP_SUCCESS != rc)
                        ldapssl_client_deinit();
                }
            }
            else
            {
                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
                             "LDAP: Invalid LDAPTrustedCAType directive - "
                             "DER_FILE or BASE64_FILE type required");
                rc = -1;
            }

        #elif APR_HAS_OPENLDAP_LDAPSDK

            /* OpenLDAP SDK supports BASE64 files
            */
            if (st->cert_file_type == LDAP_CA_TYPE_BASE64)
            {
                rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, st->cert_auth_file);
            }
            else
            {
                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
                             "LDAP: Invalid LDAPTrustedCAType directive - "
                             "BASE64_FILE type required");
                rc = -1;
            }


        #elif APR_HAS_MICROSOFT_LDAPSDK
            
            /* Microsoft SDK use the registry certificate store - always
             * assume support is always available
            */
            rc = LDAP_SUCCESS;

        #else
            rc = -1;
        #endif /* APR_HAS_NETSCAPE_LDAPSDK */

        #else  /* not compiled with SSL Support */

            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                     "LDAP: Not built with SSL support." );
            rc = -1;

        #endif /* APR_HAS_LDAP_SSL */

        if (LDAP_SUCCESS == rc)
        {
            st->ssl_support = 1;
        }
        else
        {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, 
                         "LDAP: SSL initialization failed");
            st->ssl_support = 0;
        }
    }
      
        /* The Microsoft SDK uses the registry certificate store -
         * always assume support is available
        */
    #if APR_HAS_MICROSOFT_LDAPSDK
        st->ssl_support = 1;
    #endif
    

        /* log SSL status - If SSL isn't available it isn't necessarily
         * an error because the modules asking for LDAP connections 
         * may not ask for SSL support
        */
    if (st->ssl_support)
    {
       ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                         "LDAP: SSL support available" );
    }
    else
    {
       ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                         "LDAP: SSL support unavailable" );
    }
    
#ifdef LDAP_OPT_NETWORK_TIMEOUT
    if (st->connectionTimeout > 0) {
        timeOut.tv_sec = st->connectionTimeout;
    }

    if (st->connectionTimeout >= 0) {
        rc = ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, (void *)&timeOut);
        if (APR_SUCCESS != rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "LDAP: Could not set the connection timeout" );
        }
    }
#endif

    return(OK);
}