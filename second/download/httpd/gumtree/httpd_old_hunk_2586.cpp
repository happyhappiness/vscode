                                                &so_module);
    modie = (ap_module_symbol_t *)sconf->loaded_modules->elts;
    for (i = 0; i < sconf->loaded_modules->nelts; i++) {
        modi = &modie[i];
        if (modi->name != NULL && strcmp(modi->name, modname) == 0) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0,
                          cmd->pool, "module %s is already loaded, skipping",
                          modname);
            return NULL;
        }
    }

    for (i = 0; ap_preloaded_modules[i]; i++) {
