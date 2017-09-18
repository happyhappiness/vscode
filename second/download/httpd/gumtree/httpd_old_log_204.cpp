ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "mod_include: error copying directive in %s",
                            r->filename);