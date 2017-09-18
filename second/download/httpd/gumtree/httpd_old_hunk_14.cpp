    return "AuthDigestNonceFormat is not implemented (yet)";
}

static const char *set_nc_check(cmd_parms *cmd, void *config, int flag)
{
    if (flag && !client_shm)
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0,
                     cmd->server, "Digest: WARNING: nonce-count checking "
                     "is not supported on platforms without shared-memory "
                     "support - disabling check");

    ((digest_config_rec *) config)->check_nc = flag;
    return NULL;
}

static const char *set_algorithm(cmd_parms *cmd, void *config, const char *alg)
{
    if (!strcasecmp(alg, "MD5-sess")) {
        if (!client_shm) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0,
                         cmd->server, "Digest: WARNING: algorithm `MD5-sess' "
                         "is not supported on platforms without shared-memory "
                         "support - reverting to MD5");
            alg = "MD5";
        }
    }
