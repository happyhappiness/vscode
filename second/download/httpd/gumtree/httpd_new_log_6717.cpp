ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03454)
                          "HTTP Request Line; URI incorrectly encoded: '%.*s'",
                          field_name_len(r->uri), r->uri);