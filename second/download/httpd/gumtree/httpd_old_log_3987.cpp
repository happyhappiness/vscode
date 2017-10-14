ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                                  "lua: Unable to find function %s in %s",
                                  hook_spec->function_name,
                                  hook_spec->file_name);