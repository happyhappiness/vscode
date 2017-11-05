ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "client sent unknown Transfer-Encoding "
                              "(%s): %s", tenc, r->uri);