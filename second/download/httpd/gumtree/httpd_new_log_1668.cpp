ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "HTTP Request Line; Extraneous text found '%.*s' "
                          "(perhaps whitespace was injected?)",
                          field_name_len(ll), ll);