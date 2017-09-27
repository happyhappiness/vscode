ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "query execution error saving session '%s' "
                      "in database using query '%s': %s", key, conf->selectlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));