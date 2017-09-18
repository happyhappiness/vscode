ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                                  "Within the DAV:activity-set element, the "
                                  "DAV:new element must be used, or at least "
                                  "one DAV:href must be specified.");