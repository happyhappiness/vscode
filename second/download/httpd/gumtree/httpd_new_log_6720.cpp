ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03449)
                          "HTTP Request Line; Extraneous text found '%.*s' "
                          "(perhaps whitespace was injected?)",
                          field_name_len(ll), ll);