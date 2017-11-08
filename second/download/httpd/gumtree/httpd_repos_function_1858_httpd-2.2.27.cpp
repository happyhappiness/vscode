static const char *cmd_example(cmd_parms *cmd, void *mconfig)
{
    x_cfg *cfg = (x_cfg *) mconfig;

    /*
     * "Example Wuz Here"
     */
    cfg->local = 1;
    trace_add(cmd->server, NULL, cfg, "cmd_example()");
    return NULL;
}