static const char *set_filter_note(cmd_parms *cmd, void *dummy,
                                   const char *arg1, const char *arg2)
{
    brotli_server_config_t *conf =
        ap_get_module_config(cmd->server->module_config, &brotli_module);

    if (!arg2) {
        conf->note_ratio_name = arg1;
        return NULL;
    }

    if (ap_cstr_casecmp(arg1, "Ratio") == 0) {
        conf->note_ratio_name = arg2;
    }
    else if (ap_cstr_casecmp(arg1, "Input") == 0) {
        conf->note_input_name = arg2;
    }
    else if (ap_cstr_casecmp(arg1, "Output") == 0) {
        conf->note_output_name = arg2;
    }
    else {
        return apr_psprintf(cmd->pool, "Unknown BrotliFilterNote type '%s'",
                            arg1);
    }

    return NULL;
}