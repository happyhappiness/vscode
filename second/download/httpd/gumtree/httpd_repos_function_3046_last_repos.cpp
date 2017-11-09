static const char *set_compression_quality(cmd_parms *cmd, void *dummy,
                                           const char *arg)
{
    brotli_server_config_t *conf =
        ap_get_module_config(cmd->server->module_config, &brotli_module);
    int val = atoi(arg);

    if (val < 0 || val > 11) {
        return "BrotliCompressionQuality must be between 0 and 11";
    }

    conf->quality = val;
    return NULL;
}