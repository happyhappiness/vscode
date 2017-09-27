ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                          "lua: Unable to find function %s in %s",
                          d->function_name,
                          d->spec->file);