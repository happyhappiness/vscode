ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02539)
                              "client sent unknown Transfer-Encoding "
                              "(%s): %s", tenc, r->uri);