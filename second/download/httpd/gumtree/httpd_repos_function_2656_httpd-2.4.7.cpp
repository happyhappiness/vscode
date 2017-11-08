static const char *dtraceenable(cmd_parms *cmd, void *dir, int arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    dtrace_enabled = arg;
    return NULL;
}