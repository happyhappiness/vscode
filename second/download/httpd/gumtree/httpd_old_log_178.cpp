ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "[%d] ldap cache: Setting LDAP SSL client certificate dbpath to %s.", 
                      getpid(), path);