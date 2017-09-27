ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, APLOGNO(02313)
                  "%s details: scope: %s, file: %s, func: %s",
                  what, scope_to_string(spec->scope), spec->file,
                  function ? function : "-");