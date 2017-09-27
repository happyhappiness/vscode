    ap_dbd_t *dbd = dbd_handle(r);
    apr_dbd_prepared_t *query;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;

    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01642)
                      "No query configured for %s!", action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    query = apr_hash_get(dbd->prepared, cfg->query, APR_HASH_KEY_STRING);
    if (query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01643)
                      "Error retrieving Query for %s!", action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    rv = apr_dbd_pvquery(dbd->driver, r->pool, dbd->handle, &nrows,
                         query, r->user, NULL);
    if (rv == 0) {
        if (nrows != 1) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01644)
                          "authz_dbd: %s of user %s updated %d rows",
                          action, r->user, nrows);
        }
    }
    else {
        message = apr_dbd_error(dbd->driver, dbd->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01645)
                      "authz_dbd: query for %s failed; user %s [%s]",
                      action, r->user, message?message:noerror);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (cfg->redirect == 1) {
