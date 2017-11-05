ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "could not open dbm (type %s) group access "
                      "file: %s", conf->dbmtype, conf->grpfile);