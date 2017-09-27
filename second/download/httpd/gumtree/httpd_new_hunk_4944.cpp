    }

    if (!conf->check_nc || !client_shm) {
        return OK;
    }

    if (!apr_is_empty_array(conf->qop_list) &&
        !strcasecmp(*(const char **)(conf->qop_list->elts), "none")) {
        /* qop is none, client must not send a nonce count */
        if (snc != NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01772)
                          "invalid nc %s received - no nonce count allowed when qop=none",
                          snc);
            return !OK;
