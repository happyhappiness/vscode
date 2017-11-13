static int authz_dbd_login(request_rec *r, authz_dbd_cfg *cfg,
                           const char *action)
{
    int rv;
    const char *newuri = NULL;
    int nrows;
    const char *message;
    ap_dbd_t *dbd = dbd_handle(r);
    apr_dbd_prepared_t *query;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;

    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01642)
                      "No query configured for %s!", action);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02902)
                      "No db handle available for %s! "
                      "Check your database access",
                      action);
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
        newuri = apr_table_get(r->headers_in, "Referer");
    }

    if (!newuri && cfg->redir_query) {
        query = apr_hash_get(dbd->prepared, cfg->redir_query,
                             APR_HASH_KEY_STRING);
        if (query == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01646)
                          "authz_dbd: no redirect query!");
            /* OK, this is non-critical; we can just not-redirect */
        }
        else if ((rv = apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle,
                                        &res, query, 0, r->user, NULL)) == 0) {
            for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
                 rv != -1;
                 rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
                if (rv != 0) {
                    message = apr_dbd_error(dbd->driver, dbd->handle, rv);
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01647)
                          "authz_dbd in get_row; action=%s user=%s [%s]",
                          action, r->user, message?message:noerror);
                }
                else if (newuri == NULL) {
                    newuri =
                        apr_pstrdup(r->pool,
                                    apr_dbd_get_entry(dbd->driver, row, 0));
                }
                /* we can't break out here or row won't get cleaned up */
            }
        }
        else {
            message = apr_dbd_error(dbd->driver, dbd->handle, rv);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01648)
                          "authz_dbd/redirect for %s of %s [%s]",
                          action, r->user, message?message:noerror);
        }
    }
    if (newuri != NULL) {
        r->status = HTTP_MOVED_TEMPORARILY;
        apr_table_set(r->err_headers_out, "Location", newuri);
    }
    authz_dbd_run_client_login(r, OK, action);
    return OK;
}