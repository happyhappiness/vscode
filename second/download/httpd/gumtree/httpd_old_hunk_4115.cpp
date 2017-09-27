                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01098)
                                      "Starting body due to bogus non-header "
                                      "in headers returned by %s (%s)",
                                      r->uri, r->method);
                        *pread_len = len;
                        return;
                    } else {
                         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01099)
                                       "No HTTP headers returned by %s (%s)",
                                       r->uri, r->method);
                        return;
                    }
                }
            }
            /* this is the psc->badopt == bad_ignore case */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01100)
