static const char *load_module(cmd_parms *cmd, void *dummy,
                               const char *modname, const char *filename)
{
    apr_dso_handle_t *modhandle;
    apr_dso_handle_sym_t modsym;
    module *modp;
    const char *szModuleFile = ap_server_root_relative(cmd->pool, filename);
    so_server_conf *sconf;
    ap_module_symbol_t *modi;
    ap_module_symbol_t *modie;
    int i;
    const char *error;

    /* we need to setup this value for dummy to make sure that we don't try
     * to add a non-existant tree into the build when we return to
     * execute_now.
     */
    *(ap_directive_t **)dummy = NULL;

    if (!szModuleFile) {
        return apr_pstrcat(cmd->pool, "Invalid LoadModule path ",
                           filename, NULL);
    }

    /*
     * check for already existing module
     * If it already exists, we have nothing to do
     * Check both dynamically-loaded modules and statically-linked modules.
     */
    sconf = (so_server_conf *)ap_get_module_config(cmd->server->module_config,
                                                &so_module);
    modie = (ap_module_symbol_t *)sconf->loaded_modules->elts;
    for (i = 0; i < sconf->loaded_modules->nelts; i++) {
        modi = &modie[i];
        if (modi->name != NULL && strcmp(modi->name, modname) == 0) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0,
                          cmd->pool, APLOGNO(01574) "module %s is already loaded, skipping",
                          modname);
            return NULL;
        }
    }

    for (i = 0; ap_preloaded_modules[i]; i++) {
        const char *preload_name;
        apr_size_t preload_len;
        apr_size_t thismod_len;

        modp = ap_preloaded_modules[i];

        /* make sure we're comparing apples with apples
         * make sure name of preloaded module is mod_FOO.c
         * make sure name of structure being loaded is FOO_module
         */

        if (memcmp(modp->name, "mod_", 4)) {
            continue;
        }

        preload_name = modp->name + strlen("mod_");
        preload_len = strlen(preload_name) - 2;

        if (strlen(modname) <= strlen("_module")) {
            continue;
        }
        thismod_len = strlen(modname) - strlen("_module");
        if (strcmp(modname + thismod_len, "_module")) {
            continue;
        }

        if (thismod_len != preload_len) {
            continue;
        }

        if (!memcmp(modname, preload_name, preload_len)) {
            return apr_pstrcat(cmd->pool, "module ", modname,
                               " is built-in and can't be loaded",
                               NULL);
        }
    }

    modi = apr_array_push(sconf->loaded_modules);
    modi->name = modname;

    /*
     * Load the file into the Apache address space
     */
    if (apr_dso_load(&modhandle, szModuleFile, cmd->pool) != APR_SUCCESS) {
        char my_error[256];

        return apr_pstrcat(cmd->pool, "Cannot load ", szModuleFile,
                          " into server: ",
                          apr_dso_error(modhandle, my_error, sizeof(my_error)),
                          NULL);
    }
    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, cmd->pool, APLOGNO(01575)
                 "loaded module %s", modname);

    /*
     * Retrieve the pointer to the module structure through the module name:
     * First with the hidden variant (prefix `AP_') and then with the plain
     * symbol name.
     */
    if (apr_dso_sym(&modsym, modhandle, modname) != APR_SUCCESS) {
        char my_error[256];

        return apr_pstrcat(cmd->pool, "Can't locate API module structure `",
                          modname, "' in file ", szModuleFile, ": ",
                          apr_dso_error(modhandle, my_error, sizeof(my_error)),
                          NULL);
    }
    modp = (module*) modsym;
    modp->dynamic_load_handle = (apr_dso_handle_t *)modhandle;
    modi->modp = modp;

    /*
     * Make sure the found module structure is really a module structure
     *
     */
    if (modp->magic != MODULE_MAGIC_COOKIE) {
        return apr_psprintf(cmd->pool, "API module structure '%s' in file %s "
                            "is garbled - expected signature %08lx but saw "
                            "%08lx - perhaps this is not an Apache module DSO, "
                            "or was compiled for a different Apache version?",
                            modname, szModuleFile,
                            MODULE_MAGIC_COOKIE, modp->magic);
    }

    /*
     * Add this module to the Apache core structures
     */
    error = ap_add_loaded_module(modp, cmd->pool, modname);
    if (error) {
        return error;
    }

    /*
     * Register a cleanup in the config apr_pool_t (normally pconf). When
     * we do a restart (or shutdown) this cleanup will cause the
     * shared object to be unloaded.
     */
    apr_pool_cleanup_register(cmd->pool, modi, unload_module, apr_pool_cleanup_null);

    /*
     * Finally we need to run the configuration process for the module
     */
    ap_single_module_configure(cmd->pool, cmd->server, modp);

    return NULL;
}