ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The request body does not contain "
                      "a \"propertyupdate\" element.");