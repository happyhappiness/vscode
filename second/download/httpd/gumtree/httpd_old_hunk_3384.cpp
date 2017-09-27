static const char *set_max_clients (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_daemons_limit = atoi(arg);
    return NULL;
}

static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
