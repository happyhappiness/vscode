            return HTTP_UNAUTHORIZED;
        }
    }
    else {
        const char *exp_digest;
        int match = 0, idx;
        const char **tmp = (const char **)(conf->qop_list->elts);
        for (idx = 0; idx < conf->qop_list->nelts; idx++) {
            if (!strcasecmp(*tmp, resp->message_qop)) {
                match = 1;
                break;
            }
            ++tmp;
        }

        if (!match
            && !(apr_is_empty_array(conf->qop_list)
                 && !strcasecmp(resp->message_qop, "auth"))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01793)
                          "invalid qop `%s' received: %s",
                          resp->message_qop, r->uri);
            note_digest_auth_failure(r, conf, resp, 0);
            return HTTP_UNAUTHORIZED;
