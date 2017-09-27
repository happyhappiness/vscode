ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02328)
                                "lua: Failed to obtain lua interpreter for %s %s",
                                hook_spec->function_name, hook_spec->file_name);