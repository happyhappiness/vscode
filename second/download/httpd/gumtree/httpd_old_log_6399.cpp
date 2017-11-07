ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01476)
                          "request details scope:%u, filename:%s, function:%s",
                          spec->scope,
                          spec->file,
                          hook_spec->function_name ? hook_spec->function_name : "-");