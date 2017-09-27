ap_log_error(APLOG_MARK, APLOG_WARNING,
                                     0, main_s, "_default_ VirtualHost "
                                     "overlap on port %u, the first has "
                                     "precedence", sar->host_port);