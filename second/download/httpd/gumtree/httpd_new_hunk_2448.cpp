    apr_dbd_prepared_t *query;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    const char **group;

    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01649)
                      "No query configured for dbd-group!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    query = apr_hash_get(dbd->prepared, cfg->query, APR_HASH_KEY_STRING);
    if (query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01650)
                      "Error retrieving query for dbd-group!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    rv = apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res,
                          query, 0, r->user, NULL);
    if (rv == 0) {
