ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "A prepared statement could not be found for "
                      "AuthDBDUserRealmQuery with the key '%s'", conf->realm);