ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
                      "%s is not executable; ensure interpreted scripts have "
                      "\"#!\" first line", *cmd);