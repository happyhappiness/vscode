    ((digest_config_rec *) config)->nonce_format = fmt;
    return "AuthDigestNonceFormat is not implemented (yet)";
}

static const char *set_nc_check(cmd_parms *cmd, void *config, int flag)
{
#if !APR_HAS_SHARED_MEMORY
    if (flag) {
        return "AuthDigestNcCheck: ERROR: nonce-count checking "
                     "is not supported on platforms without shared-memory "
                     "support";
    }
#endif

    ((digest_config_rec *) config)->check_nc = flag;
    return NULL;
}

static const char *set_algorithm(cmd_parms *cmd, void *config, const char *alg)
{
    if (!strcasecmp(alg, "MD5-sess")) {
        return "AuthDigestAlgorithm: ERROR: algorithm `MD5-sess' "
                "is not fully implemented";
    }
    else if (strcasecmp(alg, "MD5")) {
        return apr_pstrcat(cmd->pool, "Invalid algorithm in AuthDigestAlgorithm: ", alg, NULL);
    }

    ((digest_config_rec *) config)->algorithm = alg;
