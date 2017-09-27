ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r, APLOGNO(01568)
                          "RemoteIP: Header %s value of %s cannot be parsed "
                          "as a client IP",
                          config->header_name, parse_remote);