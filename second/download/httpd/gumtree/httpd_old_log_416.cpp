ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                         "LDAP merging Shared Cache conf: shm=0x%x rmm=0x%x for VHOST: %s",
                         st->cache_shm, st->cache_rmm, s_vhost->server_hostname);