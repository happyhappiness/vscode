ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                         "Couldn't change owner of unix domain socket %s",
                         sockname);