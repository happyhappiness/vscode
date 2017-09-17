ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                        "unable to lookup information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);