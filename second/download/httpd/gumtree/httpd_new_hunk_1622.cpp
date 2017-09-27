        if (result != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
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
            st_vhost->util_ldap_cache      = st->util_ldap_cache;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, result, s,
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp "
                         "for VHOST: %s", st->cache_shm, st->cache_rmm,
                         s_vhost->server_hostname);
#endif
            s_vhost = s_vhost->next;
        }
#if APR_HAS_SHARED_MEMORY
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
