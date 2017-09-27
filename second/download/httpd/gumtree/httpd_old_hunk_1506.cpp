                    const digest_config_rec *conf)
{
    unsigned long nc;
    const char *snc = resp->nonce_count;
    char *endptr;

    if (!conf->check_nc || !client_shm) {
        return OK;
    }

    nc = strtol(snc, &endptr, 16);
    if (endptr < (snc+strlen(snc)) && !apr_isspace(*endptr)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: invalid nc %s received - not a number", snc);
        return !OK;
    }
