ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r,
                             "%s is not executable; ensure interpreted scripts have "
                             "\"#!\" first line", 
                             r->filename);