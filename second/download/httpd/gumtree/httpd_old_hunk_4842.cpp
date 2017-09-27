        if (query == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01646)
                          "authz_dbd: no redirect query!");
            /* OK, this is non-critical; we can just not-redirect */
        }
        else if ((rv = apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle,
                                        &res, query, 0, r->user, NULL) == 0)) {
            for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
                 rv != -1;
                 rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
                if (rv != 0) {
                    message = apr_dbd_error(dbd->driver, dbd->handle, rv);
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01647)
