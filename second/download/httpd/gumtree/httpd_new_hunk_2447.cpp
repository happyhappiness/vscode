    }

    if (!newuri && cfg->redir_query) {
        query = apr_hash_get(dbd->prepared, cfg->redir_query,
                             APR_HASH_KEY_STRING);
        if (query == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01646)
                          "authz_dbd: no redirect query!");
            /* OK, this is non-critical; we can just not-redirect */
        }
        else if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res,
                                  query, 0, r->user, NULL) == 0) {
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
                    newuri = apr_dbd_get_entry(dbd->driver, row, 0);
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
