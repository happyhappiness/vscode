                      "received invalid opaque - got `%s'",
                      resp->opaque);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    if (!conf->realm) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02533)
                      "realm mismatch - got `%s' but no realm specified",
                      resp->realm);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    if (!resp->realm || strcmp(resp->realm, conf->realm)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01788)
                      "realm mismatch - got `%s' but expected `%s'",
                      resp->realm, conf->realm);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }
