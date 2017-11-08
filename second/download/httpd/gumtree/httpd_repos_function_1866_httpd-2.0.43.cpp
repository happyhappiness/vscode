static const char *include_config (cmd_parms *cmd, void *dummy,
                                   const char *name)
{
    ap_directive_t *conftree = NULL;
    const char* conffile = ap_server_root_relative(cmd->pool, name);
    
    if (!conffile) {
        return apr_pstrcat(cmd->pool, "Invalid Include path ", 
                           name, NULL);
    }

    ap_process_resource_config(cmd->server, conffile,
                               &conftree, cmd->pool, cmd->temp_pool);
    *(ap_directive_t **)dummy = conftree;
    return NULL;
}