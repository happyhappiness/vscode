static int authz_dbd_group_query(request_rec *r, authz_dbd_cfg *cfg,
                                 apr_array_header_t *groups)
{
    /* SELECT group FROM authz WHERE user = %s */
    int rv;
    const char *message;
    ap_dbd_t *dbd = dbd_handle(r);
    apr_dbd_prepared_t *query;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;

    if (cfg->query == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01649)
                      "No query configured for dbd-group!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (dbd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02903)
                      "No db handle available for dbd-query! "
                      "Check your database access");
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
        for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
             rv != -1;
             rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
            if (rv == 0) {
                APR_ARRAY_PUSH(groups, const char *) =
                    apr_pstrdup(r->pool,
                                apr_dbd_get_entry(dbd->driver, row, 0));
            }
            else {
                message = apr_dbd_error(dbd->driver, dbd->handle, rv);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01651)
                        "authz_dbd in get_row; group query for user=%s [%s]",
                        r->user, message?message:noerror);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
    }
    else {
        message = apr_dbd_error(dbd->driver, dbd->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01652)
                      "authz_dbd, in groups query for %s [%s]",
                      r->user, message?message:noerror);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    return OK;
}