ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r,
                          "RemoteIP: Header %s value of %s appears to be "
                          "a private IP or nonsensical.  Ignored",
                          config->header_name, parse_remote);