                    && d_uri.path[0] == '*' && d_uri.path[1] == '\0'))
            /* check that query matches */
            || (d_uri.query != r_uri.query
                && (!d_uri.query || !r_uri.query
                    || strcmp(d_uri.query, r_uri.query)))
            ) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: uri mismatch - <%s> does not match "
                          "request-uri <%s>", resp->uri, resp->raw_request_uri);
            return HTTP_BAD_REQUEST;
        }
    }

    if (resp->opaque && resp->opaque_num == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: received invalid opaque - got `%s'",
                      resp->opaque);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    if (strcmp(resp->realm, conf->realm)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: realm mismatch - got `%s' but expected `%s'",
                      resp->realm, conf->realm);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    if (resp->algorithm != NULL
        && strcasecmp(resp->algorithm, "MD5")
        && strcasecmp(resp->algorithm, "MD5-sess")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: unknown algorithm `%s' received: %s",
                      resp->algorithm, r->uri);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }

    return_code = get_hash(r, r->user, conf);

    if (return_code == AUTH_USER_NOT_FOUND) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: user `%s' in realm `%s' not found: %s",
                      r->user, conf->realm, r->uri);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }
    else if (return_code == AUTH_USER_FOUND) {
        /* we have a password, so continue */
    }
    else if (return_code == AUTH_DENIED) {
        /* authentication denied in the provider before attempting a match */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: user `%s' in realm `%s' denied by provider: %s",
                      r->user, conf->realm, r->uri);
        note_digest_auth_failure(r, conf, resp, 0);
        return HTTP_UNAUTHORIZED;
    }
    else {
        /* AUTH_GENERAL_ERROR (or worse)
