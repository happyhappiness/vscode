ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The \"propfind\" element does not contain one of "
                      "the required child elements (the specific command).");