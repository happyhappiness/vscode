ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Unescaped URL path matched ProxyPass; ignoring unsafe nocanon");