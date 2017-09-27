            return HTTP_UNAUTHORIZED;
        }
    }
    else {
        const char *exp_digest;
        int match = 0, idx;
        for (idx = 0; conf->qop_list[idx] != NULL; idx++) {
            if (!strcasecmp(conf->qop_list[idx], resp->message_qop)) {
                match = 1;
                break;
            }
        }

        if (!match
            && !(conf->qop_list[0] == NULL
                 && !strcasecmp(resp->message_qop, "auth"))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01793)
                          "invalid qop `%s' received: %s",
                          resp->message_qop, r->uri);
            note_digest_auth_failure(r, conf, resp, 0);
            return HTTP_UNAUTHORIZED;
