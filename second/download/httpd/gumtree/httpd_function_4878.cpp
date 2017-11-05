const char *ap_mpm_set_max_requests(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (!strcasecmp(cmd->cmd->name, "MaxRequestsPerChild")) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, APLOGNO(00545)
                     "MaxRequestsPerChild is deprecated, use "
                     "MaxConnectionsPerChild instead.");
    }

    ap_max_requests_per_child = atoi(arg);

    return NULL;
}