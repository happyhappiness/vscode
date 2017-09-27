ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "access to %s denied (filesystem path '%s') "
                              "because search permissions are missing on a "
                              "component of the path", r->uri, r->filename);