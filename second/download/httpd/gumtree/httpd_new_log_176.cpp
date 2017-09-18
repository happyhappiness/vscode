ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "unable to get information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);