    apr_file_t *out = NULL;

    if (!ap_exists_config_define("DUMP_MODULES")) {
        return;
    }

    apr_file_open_stdout(&out, p);

    apr_file_printf(out, "Loaded Modules:\n");

    sconf = (so_server_conf *)ap_get_module_config(s->module_config,
                                                   &so_module);
    for (i = 0; ; i++) {
