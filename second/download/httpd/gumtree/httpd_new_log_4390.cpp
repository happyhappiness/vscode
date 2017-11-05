ap_log_error(APLOG_MARK, APLOG_EMERG, errno,
                         ap_server_conf, APLOGNO(02171) "ufork: Possible mis-configuration "
                         "for user %s - Aborting.", user);