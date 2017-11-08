static const char *cache_negotiated_docs(cmd_parms *cmd, void *dummy,
                                         int arg)
{
    ap_set_module_config(cmd->server->module_config, &negotiation_module,
                         (arg ? "Cache" : NULL));
    return NULL;
}