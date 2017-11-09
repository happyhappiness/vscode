static const char *set_compression_lgwin(cmd_parms *cmd, void *dummy,
                                         const char *arg)
{
    brotli_server_config_t *conf =
        ap_get_module_config(cmd->server->module_config, &brotli_module);
    int val = atoi(arg);

    if (val < 10 || val > 24) {
        return "BrotliCompressionWindow must be between 10 and 24";
    }

    conf->lgwin = val;
    return NULL;
}