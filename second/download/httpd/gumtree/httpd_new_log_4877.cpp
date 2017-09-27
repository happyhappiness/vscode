ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02266)
                          "Access to %s denied for %s "
                          "(requirement expression not fulfilled)",
                          r->filename, r->useragent_ip);