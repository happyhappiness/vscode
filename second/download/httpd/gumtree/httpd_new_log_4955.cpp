ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, rv,
                          ap_server_conf, APLOGNO(02291)
                         "Cannot access directory '%s' for %s", dir, desc);