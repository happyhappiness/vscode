ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The \"update\" element does not contain "
                      "a \"label-name\" or \"version\" element.");