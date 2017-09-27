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
