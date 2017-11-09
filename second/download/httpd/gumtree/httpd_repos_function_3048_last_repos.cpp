static const char *set_compression_lgblock(cmd_parms *cmd, void *dummy,
                                           const char *arg)
{
    brotli_server_config_t *conf =
        ap_get_module_config(cmd->server->module_config, &brotli_module);
    int val = atoi(arg);

    if (val < 16 || val > 24) {
        return "BrotliCompressionMaxInputBlock must be between 16 and 24";
    }

    conf->lgblock = val;
    return NULL;
}