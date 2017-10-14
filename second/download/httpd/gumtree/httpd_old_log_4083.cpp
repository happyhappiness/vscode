ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_ENOPROC, r,
                          MODNAME ": could not execute `%s'.",
                          compr[parm->method].argv[0]);