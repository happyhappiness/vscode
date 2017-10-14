ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap cache: Setting shared memory cache size to %d bytes.", 
                      getpid(), st->cache_bytes);