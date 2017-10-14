ap_log_error(APLOG_MARK, APLOG_DEBUG, result, s, APLOGNO(01316)
                         "LDAP merging Shared Cache conf: shm=0x%pp rmm=0x%pp "
                         "for VHOST: %s", st->cache_shm, st->cache_rmm,
                         s_vhost->server_hostname);