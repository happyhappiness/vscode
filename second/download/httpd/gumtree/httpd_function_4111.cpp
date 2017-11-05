static apr_status_t dbd_load(request_rec * r, const char *key, const char **val)
{

    apr_status_t rv;
    ap_dbd_t *dbd = NULL;
    apr_dbd_prepared_t *statement = NULL;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    apr_int64_t expiry = (apr_int64_t) apr_time_now();

    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    if (conf->selectlabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "no SessionDBDselectlabel has been specified");
        return APR_EGENERAL;
    }

    rv = dbd_init(r, conf->selectlabel, &dbd, &statement);
    if (rv) {
        return rv;
    }
    rv = apr_dbd_pvbselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                          0, key, &expiry, NULL);
    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "query execution error saving session '%s' "
                      "in database using query '%s': %s", key, conf->selectlabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));
        return APR_EGENERAL;
    }
    for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
         rv != -1;
         rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
        if (rv != 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, LOG_PREFIX
                          "error retrieving results while saving '%s' "
                          "in database using query '%s': %s", key, conf->selectlabel,
                           apr_dbd_error(dbd->driver, dbd->handle, rv));
            return APR_EGENERAL;
        }
        if (*val == NULL) {
            *val = apr_dbd_get_entry(dbd->driver, row, 0);
        }
        /* we can't break out here or row won't get cleaned up */
    }

    return APR_SUCCESS;

}