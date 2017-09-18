ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                          "client sent an unrecognized expectation value of "
                          "Expect: %s", expect);