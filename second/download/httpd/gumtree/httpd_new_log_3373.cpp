ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01803)
                      "could not open dbm (type %s) group access "
                      "file: %s", conf->dbmtype, conf->grpfile);