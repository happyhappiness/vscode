ap_log_rerror(APLOG_MARK, APLOG_CRIT, status, r, APLOGNO(00529)
                              "%s pcfg_openfile: unable to check htaccess file, "
                              "ensure it is readable and that '%s' "
                              "is executable",
                              filename, d);