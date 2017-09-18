ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "user %s not in DBM group file %s: %s",
                            user, conf->auth_dbmgrpfile, r->filename);