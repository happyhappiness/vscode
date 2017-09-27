ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "could not open dbm (type %s) auth file: %s",
                      conf->dbmtype, conf->pwfile);