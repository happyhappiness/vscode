
    if (conf->nonce_lifetime > 0) {
        if (dt > conf->nonce_lifetime) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0,r,
                          "Digest: user %s: nonce expired (%.2f seconds old "
                          "- max lifetime %.2f) - sending new nonce", 
                          r->user, (double)apr_time_sec(dt),
                          (double)apr_time_sec(conf->nonce_lifetime));
            note_digest_auth_failure(r, conf, resp, 1);
            return HTTP_UNAUTHORIZED;
        }
    }
    else if (conf->nonce_lifetime == 0 && resp->client) {
        if (memcmp(resp->client->last_nonce, resp->nonce, NONCE_LEN)) {
