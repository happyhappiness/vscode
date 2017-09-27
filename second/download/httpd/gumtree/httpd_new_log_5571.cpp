ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00035)
                              "access to %s denied because search "
                              "permissions are missing on a component "
                              "of the path", r->uri);