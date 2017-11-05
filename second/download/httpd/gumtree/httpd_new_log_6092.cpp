ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03445)
                          "HTTP Request Line; Invalid method token: '%.*s'",
                          field_name_len(r->method), r->method);