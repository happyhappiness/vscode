            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Error looking up %s in database", user);
            return AUTH_GENERAL_ERROR;
        }
        if (dbd_hash == NULL) {
            dbd_hash = apr_dbd_get_entry(dbd->driver, row, 0);
        }
        /* we can't break out here or row won't get cleaned up */
    }

    if (!dbd_hash) {
        return AUTH_USER_NOT_FOUND;
