ap_log_error(APLOG_MARK, APLOG_WARNING,
                                 0, main_s, "VirtualHost %s:%u overlaps "
                                 "with VirtualHost %s:%u, the first has "
                                 "precedence, perhaps you need a "
                                 "NameVirtualHost directive",
                                 sar->virthost, sar->host_port,
                                 ic->sar->virthost, ic->sar->host_port);