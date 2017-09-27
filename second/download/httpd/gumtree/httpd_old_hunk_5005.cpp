
    rv = dbd_init(r, conf->insertlabel, &dbd, &statement);
    if (rv) {
        return rv;
    }
    rv = apr_dbd_pvbquery(dbd->driver, r->pool, dbd->handle, &rows, statement,
                          val, &expiry, key, NULL);
    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01859)
                      "query execution error inserting session '%s' "
                      "in database with '%s': %s", key, conf->insertlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));
        return APR_EGENERAL;
    }

    /*
     * if some rows were inserted it means a session was inserted, so we are
