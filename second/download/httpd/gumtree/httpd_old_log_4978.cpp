ap_log_error(APLOG_MARK, APLOG_ERR, 0, main_s,
                         "VirtualHost %s:%u -- mixing * "
                         "ports and non-* ports with "
                         "a NameVirtualHost address is not supported,"
                         " proceeding with undefined results",
                         sar->virthost, sar->host_port);