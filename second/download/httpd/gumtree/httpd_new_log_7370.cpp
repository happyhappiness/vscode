ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, "Lua hook %s:%s for phase %s did not return a numeric value", 
                              hook_spec->file_name, hook_spec->function_name, name);