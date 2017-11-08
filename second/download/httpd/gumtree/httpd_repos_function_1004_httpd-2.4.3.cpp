static const char *register_lua_root(cmd_parms *cmd, void *_cfg,
                                     const char *root)
{
    /* ap_lua_dir_cfg* cfg = (ap_lua_dir_cfg*)_cfg; */
    ap_lua_server_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                                  &lua_module);

    cfg->root_path = root;
    return NULL;
}