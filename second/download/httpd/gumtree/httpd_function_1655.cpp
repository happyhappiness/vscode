static int check_nc(const request_rec *r, const digest_header_rec *resp,
                    const digest_config_rec *conf)
{
    unsigned long nc;
    const char *snc = resp->nonce_count;
    char *endptr;

    if (conf->check_nc && !client_shm) {
        /* Shouldn't happen, but just in case... */
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "Digest: cannot check nonce count without shared memory");
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: invalid nc %s received - no nonce count allowed when qop=none",
                          snc);
            return !OK;
        }
        /* qop is none, cannot check nonce count */
        return OK;
    }

    nc = strtol(snc, &endptr, 16);
    if (endptr < (snc+strlen(snc)) && !apr_isspace(*endptr)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nc %s received - not a number", snc);
        return !OK;
    }

    if (!resp->client) {
        return !OK;
    }

    if (nc != resp->client->nonce_count) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: Warning, possible replay attack: nonce-count "
                      "check failed: %lu != %lu", nc,
                      resp->client->nonce_count);
        return !OK;
    }

    return OK;
}