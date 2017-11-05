static apr_status_t compile_sed_expr(sed_expr_config *sed_cfg,
                                     cmd_parms *cmd,
                                     const char *expr)
{
    apr_status_t status = APR_SUCCESS;

    if (!sed_cfg->sed_cmds) {
        sed_commands_t *sed_cmds;
        sed_cmds = apr_pcalloc(cmd->pool, sizeof(sed_commands_t));
        status = sed_init_commands(sed_cmds, sed_compile_errf, sed_cfg,
                                   cmd->pool);
        if (status != APR_SUCCESS) {
            sed_destroy_commands(sed_cmds);
            return status;
        }
        sed_cfg->sed_cmds = sed_cmds;
    }
    status = sed_compile_string(sed_cfg->sed_cmds, expr);
    if (status != APR_SUCCESS) {
        sed_destroy_commands(sed_cfg->sed_cmds);
        sed_cfg->sed_cmds = NULL;
    }
    return status;
}