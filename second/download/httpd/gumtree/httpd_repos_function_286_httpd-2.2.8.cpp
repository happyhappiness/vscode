static const char *dav_fs_cmd_davlockdb(cmd_parms *cmd, void *config,
                                        const char *arg1)
{
    dav_fs_server_conf *conf;
    conf = ap_get_module_config(cmd->server->module_config,
                                &dav_fs_module);
    conf->lockdb_path = ap_server_root_relative(cmd->pool, arg1);

    if (!conf->lockdb_path) {
        return apr_pstrcat(cmd->pool, "Invalid DAVLockDB path ",
                           arg1, NULL);
    }

    return NULL;
}