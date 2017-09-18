    apr_time_t dt;
    int len;
    time_rec nonce_time;
    char tmp, hash[NONCE_HASH_LEN+1];

    if (strlen(resp->nonce) != NONCE_LEN) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: invalid nonce %s received - length is not %d",
                      resp->nonce, NONCE_LEN);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

