ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "Lua hook %s:%s for phase %s returned %d", 
                              hook_spec->file_name, hook_spec->function_name, name, rc);