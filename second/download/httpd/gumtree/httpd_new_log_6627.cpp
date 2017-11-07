ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01859)
                      "query execution error inserting session '%s' "
                      "in database with '%s': %s", newkey, conf->insertlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));