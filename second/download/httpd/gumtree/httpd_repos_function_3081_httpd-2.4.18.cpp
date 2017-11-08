static const char *
unixd_set_suexec(cmd_parms *cmd, void *dummy, int arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (!ap_unixd_config.suexec_enabled && arg) {
        return apr_pstrcat(cmd->pool, "suEXEC isn't supported: ",
                           ap_unixd_config.suexec_disabled_reason, NULL);
    }

    if (!arg) {
        ap_unixd_config.suexec_disabled_reason = "Suexec directive is Off";
    }

    ap_unixd_config.suexec_enabled = arg;
    return NULL;
}