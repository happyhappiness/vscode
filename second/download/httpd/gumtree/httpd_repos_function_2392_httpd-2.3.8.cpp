static const char *noloris_max_conn(cmd_parms *cmd, void *cfg, const char *val)
{
    const char* err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (!err) {
        default_max_connections = atoi(val);
    }
    return err;
}