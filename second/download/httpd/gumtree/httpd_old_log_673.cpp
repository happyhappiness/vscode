ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, 
                     "Couldn't bind unix domain socket %s",
                     sconf->sockname);