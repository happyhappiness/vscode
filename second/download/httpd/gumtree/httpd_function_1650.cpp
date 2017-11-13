static const char *set_nc_check(cmd_parms *cmd, void *config, int flag)
{
    if (flag && !client_shm)
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                     cmd->server, "Digest: WARNING: nonce-count checking "
                     "is not supported on platforms without shared-memory "
                     "support - disabling check");

    ((digest_config_rec *) config)->check_nc = flag;
    return NULL;
}