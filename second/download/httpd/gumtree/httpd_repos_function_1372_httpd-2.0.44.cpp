static const char *deflate_set_note(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    deflate_filter_config *c = ap_get_module_config(cmd->server->module_config,
                                                    &deflate_module);
    c->noteName = apr_pstrdup(cmd->pool, arg);

    return NULL;
}