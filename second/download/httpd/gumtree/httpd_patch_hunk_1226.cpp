                                             &ldap_module);
 
 #if APR_HAS_SHARED_MEMORY
             st_vhost->cache_shm = st->cache_shm;
             st_vhost->cache_rmm = st->cache_rmm;
             st_vhost->cache_file = st->cache_file;
+            st_vhost->util_ldap_cache = st->util_ldap_cache;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, result, s,
                          "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp "
                          "for VHOST: %s", st->cache_shm, st->cache_rmm,
                          s_vhost->server_hostname);
 #endif
             st_vhost->lock_file = st->lock_file;
