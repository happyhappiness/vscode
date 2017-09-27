        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    tmp = resp->nonce[NONCE_TIME_LEN];
    resp->nonce[NONCE_TIME_LEN] = '\0';
    len = apr_base64_decode_binary(nonce_time.arr, resp->nonce);
    gen_nonce_hash(hash, resp->nonce, resp->opaque, r->server, conf);
    resp->nonce[NONCE_TIME_LEN] = tmp;
    resp->nonce_time = nonce_time.time;

    if (strcmp(hash, resp->nonce+NONCE_TIME_LEN)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
