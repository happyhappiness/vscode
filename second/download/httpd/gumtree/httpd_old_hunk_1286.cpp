        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: Require ThreadLimit > 0, setting to 1");
        thread_limit = 1;
    }
    return NULL;
}
static const char *set_disable_acceptex(cmd_parms *cmd, void *dummy, char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    if (use_acceptex) {
