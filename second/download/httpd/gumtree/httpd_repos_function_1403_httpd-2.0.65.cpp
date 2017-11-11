static const char *deflate_set_compressionlevel(cmd_parms *cmd, void *dummy,
                                        const char *arg)
{
    deflate_filter_config *c = ap_get_module_config(cmd->server->module_config,
                                                    &deflate_module);
    int i;

    i = atoi(arg);

    if (i < 1 || i > 9)
        return "Compression Level must be between 1 and 9";

    c->compressionlevel = i;

    return NULL;
}