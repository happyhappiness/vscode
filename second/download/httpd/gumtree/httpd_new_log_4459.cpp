ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01098)
                                      "Starting body due to bogus non-header "
                                      "in headers returned by %s (%s)",
                                      r->uri, r->method);