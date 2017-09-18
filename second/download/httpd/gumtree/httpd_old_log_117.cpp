ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The \"label\" element does not contain "
                      "an \"add\", \"set\", or \"remove\" element.");