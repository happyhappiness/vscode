ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "unable to get information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);