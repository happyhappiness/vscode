ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "query execution error updating session '%s' "
                      "using database query '%s': %s", key, conf->updatelabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));