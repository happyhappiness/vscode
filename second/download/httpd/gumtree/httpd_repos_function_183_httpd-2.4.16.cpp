static const char *dav_lock_cmd_davlockdb(cmd_parms *cmd, void *config,
                                        const char *arg1)
{
    dav_lock_dir_conf *conf = config;

    conf->lockdb_path = ap_server_root_relative(cmd->pool, arg1);

    if (!conf->lockdb_path) {
        return apr_pstrcat(cmd->pool, "Invalid DAVGenericLockDB path ",
                           arg1, NULL);
    }

    return NULL;
}