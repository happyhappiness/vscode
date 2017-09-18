

    /* check for existence and syntax of Auth header */

    if (resp->auth_hdr_sts != VALID) {
        if (resp->auth_hdr_sts == NOT_DIGEST) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: client used wrong authentication scheme "
                          "`%s': %s", resp->scheme, r->uri);
        }
        else if (resp->auth_hdr_sts == INVALID) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "Digest: missing user, realm, nonce, uri, digest, "
                          "cnonce, or nonce_count in authorization header: %s",
                          r->uri);
        }
        /* else (resp->auth_hdr_sts == NO_HEADER) */
        note_digest_auth_failure(r, conf, resp, 0);
