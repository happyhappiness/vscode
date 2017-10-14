ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL,
                             "Couldn't unlink unix domain socket %s",
                             sockname);