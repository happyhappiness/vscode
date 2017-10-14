ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01854)
                      "query execution error saving session '%s' "
                      "in database using query '%s': %s", key, conf->selectlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));