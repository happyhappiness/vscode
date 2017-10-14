static const char *set_disable_acceptex(cmd_parms *cmd, void *dummy)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    if (use_acceptex) {
        use_acceptex = 0;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL,
                     "Disabled use of AcceptEx() WinSock2 API");
    }
    return NULL;
}