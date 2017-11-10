const char * ap_mpm_set_graceful_shutdown(cmd_parms *cmd, void *dummy,
                                          const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    ap_graceful_shutdown_timeout = atoi(arg);
    return NULL;
}