    if (!conf->check_nc || !client_shm) {
        return OK;
    }

    nc = strtol(snc, &endptr, 16);
    if (endptr < (snc+strlen(snc)) && !apr_isspace(*endptr)) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: invalid nc %s received - not a number", snc);
        return !OK;
    }

    if (!resp->client) {
        return !OK;
    }

    if (nc != resp->client->nonce_count) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Digest: Warning, possible replay attack: nonce-count "
                      "check failed: %lu != %lu", nc,
                      resp->client->nonce_count);
        return !OK;
    }

