ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, ap_server_conf,
                     "Child %d: Marked listeners as not inheritable.", my_pid);