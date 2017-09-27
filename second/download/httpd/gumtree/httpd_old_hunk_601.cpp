                      "Digest: unknown algorithm `%s' received: %s",
                      resp->algorithm, r->uri);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    if (!conf->pwfile) {
        return DECLINED;
    }

    if (!(conf->ha1 = get_hash(r, r->user, conf->realm, conf->pwfile))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: user `%s' in realm `%s' not found: %s",
                      r->user, conf->realm, r->uri);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    
    if (resp->message_qop == NULL) {
        /* old (rfc-2069) style digest */
        if (strcmp(resp->digest, old_digest(r, resp, conf->ha1))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: user %s: password mismatch: %s", r->user,
                          r->uri);
