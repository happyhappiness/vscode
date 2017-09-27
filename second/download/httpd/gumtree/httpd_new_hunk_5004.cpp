    }

    rv = dbd_init(r, conf->updatelabel, &dbd, &statement);
    if (rv) {
        return rv;
    }

    if (oldkey) {
        rv = apr_dbd_pvbquery(dbd->driver, r->pool, dbd->handle, &rows,
                statement, val, &expiry, newkey, oldkey, NULL);
        if (rv) {
            ap_log_rerror(
                    APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01857) "query execution error updating session '%s' "
                    "using database query '%s': %s/%s", oldkey, newkey, conf->updatelabel, apr_dbd_error(dbd->driver, dbd->handle, rv));
            return APR_EGENERAL;
        }

        /*
         * if some rows were updated it means a session existed and was updated,
         * so we are done.
         */
        if (rows != 0) {
            return APR_SUCCESS;
        }
    }

    if (conf->insertlabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01858)
                      "no SessionDBDinsertlabel has been specified");
        return APR_EGENERAL;
