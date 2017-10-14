static void dump_loaded_modules(apr_pool_t *p, server_rec *s)
{
    ap_module_symbol_t *modie;
    ap_module_symbol_t *modi;
    so_server_conf *sconf;
    int i;
    apr_file_t *out = NULL;

    if (!ap_exists_config_define("DUMP_MODULES")) {
        return;
    }

    apr_file_open_stderr(&out, p);

    apr_file_printf(out, "Loaded Modules:\n");

    sconf = (so_server_conf *)ap_get_module_config(s->module_config,
                                                   &so_module);
    for (i = 0; ; i++) {
        modi = &ap_prelinked_module_symbols[i];
        if (modi->name != NULL) {
            apr_file_printf(out, " %s (static)\n", modi->name);
        }
        else {
            break;
        }
    }

    modie = (ap_module_symbol_t *)sconf->loaded_modules->elts;
    for (i = 0; i < sconf->loaded_modules->nelts; i++) {
        modi = &modie[i];
        if (modi->name != NULL) {
            apr_file_printf(out, " %s (shared)\n", modi->name);
        }
    }
}