ap_log_rerror(APLOG_MARK, APLOG_CRIT, status, r,
                              "%s pcfg_openfile: unable to check htaccess file, "
                              "ensure it is readable",
                              filename);