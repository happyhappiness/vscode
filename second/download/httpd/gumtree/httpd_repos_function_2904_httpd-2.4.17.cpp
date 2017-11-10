static apr_status_t dbd_remove(request_rec * r, const char *key)
{

    apr_status_t rv;
    ap_dbd_t *dbd;
    apr_dbd_prepared_t *statement;
    int rows = 0;

    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    if (conf->deletelabel == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01862)
                      "no SessionDBDdeletelabel has been specified");
        return APR_EGENERAL;
    }

    rv = dbd_init(r, conf->deletelabel, &dbd, &statement);
    if (rv != APR_SUCCESS) {
        /* No need to do additional error logging here, it has already
           been done in dbd_init if needed */
        return rv;
    }

    rv = apr_dbd_pvbquery(dbd->driver, r->pool, dbd->handle, &rows, statement,
                          key, NULL);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01864)
                      "query execution error removing session '%s' "
                      "from database", key);
        return rv;
    }

    return APR_SUCCESS;

}