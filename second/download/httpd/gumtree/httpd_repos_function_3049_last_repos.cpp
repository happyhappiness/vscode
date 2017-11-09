static const char *set_etag_mode(cmd_parms *cmd, void *dummy,
                                 const char *arg)
{
    brotli_server_config_t *conf =
        ap_get_module_config(cmd->server->module_config, &brotli_module);

    if (ap_cstr_casecmp(arg, "AddSuffix") == 0) {
        conf->etag_mode = ETAG_MODE_ADDSUFFIX;
    }
    else if (ap_cstr_casecmp(arg, "NoChange") == 0) {
        conf->etag_mode = ETAG_MODE_NOCHANGE;
    }
    else if (ap_cstr_casecmp(arg, "Remove") == 0) {
        conf->etag_mode = ETAG_MODE_REMOVE;
    }
    else {
        return "BrotliAlterETag accepts only 'AddSuffix', 'NoChange' and 'Remove'";
    }

    return NULL;
}