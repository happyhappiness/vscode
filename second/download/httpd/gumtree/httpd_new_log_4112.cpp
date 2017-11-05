ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01855)
                          "error retrieving results while saving '%s' "
                          "in database using query '%s': %s", key, conf->selectlabel,
                           apr_dbd_error(dbd->driver, dbd->handle, rv));