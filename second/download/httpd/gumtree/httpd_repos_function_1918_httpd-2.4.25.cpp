static const char *cmd_hm_storage(cmd_parms *cmd,
                                  void *dconf, const char *path)
{
    apr_pool_t *p = cmd->pool;
    hm_ctx_t *ctx =
        (hm_ctx_t *) ap_get_module_config(cmd->server->module_config,
                                          &heartmonitor_module);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    ctx->storage_path = ap_runtime_dir_relative(p, path);

    return NULL;
}