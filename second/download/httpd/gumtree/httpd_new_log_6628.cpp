ap_log_rerror(
                    APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01857) "query execution error updating session '%s' "
                    "using database query '%s': %s/%s", oldkey, newkey, conf->updatelabel, apr_dbd_error(dbd->driver, dbd->handle, rv));