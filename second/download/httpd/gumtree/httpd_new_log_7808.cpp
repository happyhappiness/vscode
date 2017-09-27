ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01478)
                               "lua: Unable to find entry function '%s' in %s (not a valid function)",
                                  hook_spec->function_name,
                                  hook_spec->file_name);