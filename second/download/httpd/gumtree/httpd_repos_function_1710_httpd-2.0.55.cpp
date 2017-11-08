static const char *set_algorithm(cmd_parms *cmd, void *config, const char *alg)
{
    if (!strcasecmp(alg, "MD5-sess")) {
        if (!client_shm) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         cmd->server, "Digest: WARNING: algorithm `MD5-sess' "
                         "is not supported on platforms without shared-memory "
                         "support - reverting to MD5");
            alg = "MD5";
        }
    }
    else if (strcasecmp(alg, "MD5")) {
        return apr_pstrcat(cmd->pool, "Invalid algorithm in AuthDigestAlgorithm: ", alg, NULL);
    }

    ((digest_config_rec *) config)->algorithm = alg;
    return NULL;
}