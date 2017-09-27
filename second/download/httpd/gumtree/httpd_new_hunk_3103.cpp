
}

/**
 * Save the session by the key specified.
 */
static apr_status_t dbd_save(request_rec * r, const char *key, const char *val,
                             apr_int64_t expiry)
{

    apr_status_t rv;
    ap_dbd_t *dbd = NULL;
    apr_dbd_prepared_t *statement;
    int rows = 0;

    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    if (conf->updatelabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01856)
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01857)
                      "query execution error updating session '%s' "
                      "using database query '%s': %s", key, conf->updatelabel,
                      apr_dbd_error(dbd->driver, dbd->handle, rv));
        return APR_EGENERAL;
    }

