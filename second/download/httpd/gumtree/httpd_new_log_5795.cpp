ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "h2_h2(%ld): tls protocol not suitable: %s", 
                          (long)c->id, val);