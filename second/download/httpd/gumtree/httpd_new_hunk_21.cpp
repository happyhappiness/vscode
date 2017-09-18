    len = apr_base64_decode_binary(nonce_time.arr, resp->nonce);
    gen_nonce_hash(hash, resp->nonce, resp->opaque, r->server, conf);
    resp->nonce[NONCE_TIME_LEN] = tmp;
    resp->nonce_time = nonce_time.time;

    if (strcmp(hash, resp->nonce+NONCE_TIME_LEN)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - hash is not %s",
                      resp->nonce, hash);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    dt = r->request_time - nonce_time.time;
    if (conf->nonce_lifetime > 0 && dt < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - user attempted "
                      "time travel", resp->nonce);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    if (conf->nonce_lifetime > 0) {
        if (dt > conf->nonce_lifetime) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0,r,
                          "Digest: user %s: nonce expired (%.2f seconds old "
                          "- max lifetime %.2f) - sending new nonce", 
                          r->user, ((double)dt)/APR_USEC_PER_SEC, 
                          ((double)(conf->nonce_lifetime))/APR_USEC_PER_SEC);
            note_digest_auth_failure(r, conf, resp, 1);
            return HTTP_UNAUTHORIZED;
        }
    }
    else if (conf->nonce_lifetime == 0 && resp->client) {
        if (memcmp(resp->client->last_nonce, resp->nonce, NONCE_LEN)) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Digest: user %s: one-time-nonce mismatch - sending "
                          "new nonce", r->user);
            note_digest_auth_failure(r, conf, resp, 1);
            return HTTP_UNAUTHORIZED;
        }
    }
