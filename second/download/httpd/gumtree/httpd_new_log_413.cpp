ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                 "[%" APR_PID_T_FMT "] ldap cache: Setting shared memory "
                 " cache size to %" APR_SIZE_T_FMT " bytes.", 
                 getpid(), st->cache_bytes);