ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                           "unknown value \"%s\" to parameter \"encoding\" of "
                           "tag echo in %s", tag_val, r->filename);