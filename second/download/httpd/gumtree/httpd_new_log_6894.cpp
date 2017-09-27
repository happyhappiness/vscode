ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02418)
                          "HTTP Request Line; Unrecognized protocol '%.*s' "
                          "(perhaps whitespace was injected?)",
                          field_name_len(r->protocol), r->protocol);