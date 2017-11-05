ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "HTTP Request Line; Unable to parse URI: '%.*s'",
                      field_name_len(r->uri), r->uri);