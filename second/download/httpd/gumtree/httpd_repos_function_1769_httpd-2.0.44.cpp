static const char *execute_now(char *cmd_line, const char *args,
                               cmd_parms *parms,
                               apr_pool_t *p, apr_pool_t *ptemp,
                               ap_directive_t **sub_tree,
                               ap_directive_t *parent)
{
    module *mod = ap_top_module;
    const command_rec *cmd;

    if (!(cmd = ap_find_command_in_modules(cmd_line, &mod))) {
        return apr_pstrcat(parms->pool, "Invalid command '",
                           cmd_line,
                           "', perhaps mis-spelled or defined by a module "
                           "not included in the server configuration",
                           NULL);
    }
    else {
        return invoke_cmd(cmd, parms, sub_tree, args);
    }
}