            }
        }

        if (!match
            && !(conf->qop_list[0] == NULL
                 && !strcasecmp(resp->message_qop, "auth"))) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: invalid qop `%s' received: %s",
                          resp->message_qop, r->uri);
            note_digest_auth_failure(r, conf, resp, 0);
            return HTTP_UNAUTHORIZED;
        }

        exp_digest = new_digest(r, resp, conf);
        if (!exp_digest) {
            /* we failed to allocate a client struct */
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        if (strcmp(resp->digest, exp_digest)) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: user %s: password mismatch: %s", r->user,
                          r->uri);
            note_digest_auth_failure(r, conf, resp, 0);
            return HTTP_UNAUTHORIZED;
        }
    }
