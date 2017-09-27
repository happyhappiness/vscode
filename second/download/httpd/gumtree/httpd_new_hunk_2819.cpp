
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

