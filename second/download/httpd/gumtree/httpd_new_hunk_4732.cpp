    modi = apr_array_push(sconf->loaded_modules);
    modi->name = modname;

    /*
     * Load the file into the Apache address space
     */
    error = dso_load(cmd, &modhandle, filename, &module_file);
    if (error)
        return error;
    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, cmd->pool, APLOGNO(01575)
                 "loaded module %s from %s", modname, module_file);

    /*
     * Retrieve the pointer to the module structure through the module name:
     * First with the hidden variant (prefix `AP_') and then with the plain
     * symbol name.
     */
    if (apr_dso_sym(&modsym, modhandle, modname) != APR_SUCCESS) {
        char my_error[256];

        return apr_pstrcat(cmd->pool, "Can't locate API module structure `",
                          modname, "' in file ", module_file, ": ",
                          apr_dso_error(modhandle, my_error, sizeof(my_error)),
                          NULL);
    }
    modp = (module*) modsym;
    modp->dynamic_load_handle = (apr_dso_handle_t *)modhandle;
    modi->modp = modp;
