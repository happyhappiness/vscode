
        /* calculate rspauth attribute
         */
        if (resp->algorithm && !strcasecmp(resp->algorithm, "MD5-sess")) {
            ha1 = get_session_HA1(r, resp, conf, 0);
            if (!ha1) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01795)
                              "internal error: couldn't find session "
                              "info for user %s", resp->username);
                return !OK;
            }
        }
        else {
            ha1 = conf->ha1;
