static const char *sed_add_expr(cmd_parms *cmd, void *cfg, const char *arg)
{
    int offset = (int) (long) cmd->info;
    sed_expr_config *sed_cfg =
                (sed_expr_config *) (((char *) cfg) + offset);
    if (compile_sed_expr(sed_cfg, cmd, arg) != APR_SUCCESS) {
        return apr_psprintf(cmd->temp_pool,
                            "Failed to compile sed expression. %s",
                            sed_cfg->last_error);
    }
    return NULL;
}