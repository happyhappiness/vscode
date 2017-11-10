static const char *cmd_lb_hb_storage(cmd_parms *cmd,
                                  void *dconf, const char *path)
{
    apr_pool_t *p = cmd->pool;
    lb_hb_ctx_t *ctx =
    (lb_hb_ctx_t *) ap_get_module_config(cmd->server->module_config,
                                         &lbmethod_heartbeat_module);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    ctx->path = ap_runtime_dir_relative(p, path);

    return NULL;
}