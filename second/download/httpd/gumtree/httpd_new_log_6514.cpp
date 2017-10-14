ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                          "setting alpn protos from '%s', protolen=%d", 
                          alpn_note, (int)(s - protos));