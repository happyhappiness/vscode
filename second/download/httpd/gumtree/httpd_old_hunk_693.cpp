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
    ap_add_loaded_module(modp, cmd->pool);

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

/* 
 * This implements the LoadFile directive and loads an arbitrary
 * shared object file into the adress space of the server process.
 */

static const char *load_file(cmd_parms *cmd, void *dummy, const char *filename)
{
    apr_dso_handle_t *handle;
    const char *file;

    file = ap_server_root_relative(cmd->pool, filename);
    
    if (!file) {
        return apr_pstrcat(cmd->pool, "Invalid LoadFile path ", 
                           filename, NULL);
    }

    if (apr_dso_load(&handle, file, cmd->pool) != APR_SUCCESS) {
        char my_error[256];

	return apr_pstrcat(cmd->pool, "Cannot load ", filename, 
			  " into server: ", 
			  apr_dso_error(handle, my_error, sizeof(my_error)),
			  NULL);
    }
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
		 "loaded file %s", filename);

    return NULL;
}

#else /* not NO_DLOPEN */

static const char *load_file(cmd_parms *cmd, void *dummy, const char *filename)
{
    ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, cmd->pool, 
                 "WARNING: LoadFile not supported on this platform");
    return NULL;
}

static const char *load_module(cmd_parms *cmd, void *dummy, 
	                       const char *modname, const char *filename)
{
    ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, cmd->pool, 
                 "WARNING: LoadModule not supported on this platform");
    return NULL;
}

#endif /* NO_DLOPEN */

static const command_rec so_cmds[] = {
    AP_INIT_TAKE2("LoadModule", load_module, NULL, RSRC_CONF | EXEC_ON_READ,
      "a module name and the name of a shared object file to load it from"),
    AP_INIT_ITERATE("LoadFile", load_file, NULL, RSRC_CONF  | EXEC_ON_READ,
      "shared object file or library to load into the server at runtime"),
    { NULL }
};

module AP_MODULE_DECLARE_DATA so_module = {
   STANDARD20_MODULE_STUFF,
   NULL,			    /* create per-dir config */
   NULL,			    /* merge per-dir config */
   so_sconf_create,		/* server config */
   NULL,			    /* merge server config */
   so_cmds,			    /* command apr_table_t */
   NULL				    /* register hooks */
};
