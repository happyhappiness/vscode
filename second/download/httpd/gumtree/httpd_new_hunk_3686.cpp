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
