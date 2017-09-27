    }

    if (!conf->check_nc || !client_shm) {
        return OK;
    }

    if ((conf->qop_list != NULL)
        &&(conf->qop_list[0] != NULL)
        &&!strcasecmp(conf->qop_list[0], "none")) {
        /* qop is none, client must not send a nonce count */
        if (snc != NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01772)
                          "invalid nc %s received - no nonce count allowed when qop=none",
                          snc);
            return !OK;
