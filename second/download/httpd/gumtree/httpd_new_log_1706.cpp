ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap connection: Setting connection timeout to %ld seconds.", 
                      getpid(), st->connectionTimeout);