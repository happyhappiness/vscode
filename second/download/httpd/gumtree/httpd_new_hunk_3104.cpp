     */
    if (rows != 0) {
        return APR_SUCCESS;
    }

    if (conf->insertlabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01858)
                      "no SessionDBDinsertlabel has been specified");
        return APR_EGENERAL;
    }

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

