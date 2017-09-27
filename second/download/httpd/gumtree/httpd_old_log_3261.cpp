ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Could not open dbm (type %s) hash file: %s",
                      conf->dbmtype, conf->pwfile);