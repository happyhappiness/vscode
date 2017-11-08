static const char *set_hc_tpsize (cmd_parms *cmd, void *dummy, const char *arg)
{
    sctx_t *ctx;

    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    ctx = (sctx_t *) ap_get_module_config(cmd->server->module_config,
                                          &proxy_hcheck_module);

    ctx->tpsize = atoi(arg);
    if (ctx->tpsize < 0)
        return "Invalid ProxyHCTPsize parameter. Parameter must be "
               ">= 0";
    return NULL;
}