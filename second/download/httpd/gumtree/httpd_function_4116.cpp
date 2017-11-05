static apr_status_t dbd_save(request_rec * r, const char *key, const char *val, apr_int64_t expiry)
{

    apr_status_t rv;
    ap_dbd_t *dbd = NULL;
    apr_dbd_prepared_t *statement;
    int rows = 0;

    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    if (conf->updatelabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "no SessionDBDupdatelabel has been specified");
        return APR_EGENERAL;
    }

    rv = dbd_init(r, conf->updatelabel, &dbd, &statement);
    if (rv) {
        return rv;
    }
    rv = apr_dbd_pvbquery(dbd->driver, r->pool, dbd->handle, &rows, statement,
                          val, &expiry, key, NULL);
    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "query execution error updating session '%s' "
                      "using database query '%s': %s", key, conf->updatelabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));
        return APR_EGENERAL;
    }

    /*
     * if some rows were updated it means a session existed and was updated,
     * so we are done.
     */
    if (rows != 0) {
        return APR_SUCCESS;
    }

    if (conf->insertlabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, LOG_PREFIX
                      "query execution error inserting session '%s' "
                      "in database with '%s': %s", key, conf->insertlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));
        return APR_EGENERAL;
    }

    /*
     * if some rows were inserted it means a session was inserted, so we are
     * done.
     */
    if (rows != 0) {
        return APR_SUCCESS;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                  "the session insert query did not cause any rows to be added "
                  "to the database for session '%s', session not inserted", key);

    return APR_EGENERAL;

}