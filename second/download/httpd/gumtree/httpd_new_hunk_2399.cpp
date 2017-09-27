    unsigned long nc;
    const char *snc = resp->nonce_count;
    char *endptr;

    if (conf->check_nc && !client_shm) {
        /* Shouldn't happen, but just in case... */
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01771)
                      "cannot check nonce count without shared memory");
        return OK;
    }

    if (!conf->check_nc || !client_shm) {
        return OK;
    }

    if ((conf->qop_list != NULL)
        &&(conf->qop_list[0] != NULL)
        &&!strcasecmp(conf->qop_list[0], "none")) {
        /* qop is none, client must not send a nonce count */
        if (snc != NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01772)
                          "invalid nc %s received - no nonce count allowed when qop=none",
                          snc);
            return !OK;
        }
        /* qop is none, cannot check nonce count */
        return OK;
    }

    nc = strtol(snc, &endptr, 16);
    if (endptr < (snc+strlen(snc)) && !apr_isspace(*endptr)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01773)
                      "invalid nc %s received - not a number", snc);
        return !OK;
    }

    if (!resp->client) {
        return !OK;
    }

    if (nc != resp->client->nonce_count) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01774)
                      "Warning, possible replay attack: nonce-count "
                      "check failed: %lu != %lu", nc,
                      resp->client->nonce_count);
        return !OK;
    }

    return OK;
}

static int check_nonce(request_rec *r, digest_header_rec *resp,
                       const digest_config_rec *conf)
{
    apr_time_t dt;
    time_rec nonce_time;
    char tmp, hash[NONCE_HASH_LEN+1];

    if (strlen(resp->nonce) != NONCE_LEN) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01775)
                      "invalid nonce %s received - length is not %d",
                      resp->nonce, NONCE_LEN);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    tmp = resp->nonce[NONCE_TIME_LEN];
    resp->nonce[NONCE_TIME_LEN] = '\0';
    apr_base64_decode_binary(nonce_time.arr, resp->nonce);
    gen_nonce_hash(hash, resp->nonce, resp->opaque, r->server, conf);
    resp->nonce[NONCE_TIME_LEN] = tmp;
    resp->nonce_time = nonce_time.time;

    if (strcmp(hash, resp->nonce+NONCE_TIME_LEN)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01776)
                      "invalid nonce %s received - hash is not %s",
                      resp->nonce, hash);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    dt = r->request_time - nonce_time.time;
    if (conf->nonce_lifetime > 0 && dt < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01777)
                      "invalid nonce %s received - user attempted "
                      "time travel", resp->nonce);
        note_digest_auth_failure(r, conf, resp, 1);
        return HTTP_UNAUTHORIZED;
    }

    if (conf->nonce_lifetime > 0) {
        if (dt > conf->nonce_lifetime) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0,r, APLOGNO(01778)
                          "user %s: nonce expired (%.2f seconds old "
                          "- max lifetime %.2f) - sending new nonce",
                          r->user, (double)apr_time_sec(dt),
                          (double)apr_time_sec(conf->nonce_lifetime));
            note_digest_auth_failure(r, conf, resp, 1);
            return HTTP_UNAUTHORIZED;
        }
    }
    else if (conf->nonce_lifetime == 0 && resp->client) {
        if (memcmp(resp->client->last_nonce, resp->nonce, NONCE_LEN)) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01779)
                          "user %s: one-time-nonce mismatch - sending "
                          "new nonce", r->user);
            note_digest_auth_failure(r, conf, resp, 1);
            return HTTP_UNAUTHORIZED;
        }
    }
    /* else (lifetime < 0) => never expires */
