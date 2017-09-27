ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02483)
                              "lua: Lua handler %s in %s did not return a value, assuming apache2.OK",
                              function_name,
                              filename);