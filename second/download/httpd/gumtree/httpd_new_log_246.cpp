ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "execution failure for parameter \"%s\" "
                            "to tag exec in file %s",
                            tag, r->filename);