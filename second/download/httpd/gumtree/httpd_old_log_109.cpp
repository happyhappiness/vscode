ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                          "The request body, if present, must be a "
                          "DAV:checkin element.");