ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "ldap_simple_bind() failed with server down "
                      "(try %d)", failures + 1);