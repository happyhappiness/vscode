static const char *set_use_digest_algorithm(cmd_parms *cmd, void *config,
                                            const char *alg)
{
    auth_basic_config_rec *conf = (auth_basic_config_rec *)config;

    if (strcasecmp(alg, "Off") && strcasecmp(alg, "MD5")) {
        return apr_pstrcat(cmd->pool,
                           "Invalid algorithm in "
                           "AuthBasicUseDigestAlgorithm: ", alg, NULL);
    }

    conf->use_digest_algorithm = alg;
    conf->use_digest_algorithm_set = 1;

    return NULL;
}