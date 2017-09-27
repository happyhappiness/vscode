ap_log_error(APLOG_MARK,
                                     APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                                     "bad cumulated nesting (%+d) in %s",
                                     any_nesting, where);