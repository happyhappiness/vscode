    /* destroy the module information */
    modi->modp = NULL;
    modi->name = NULL;
    return APR_SUCCESS;
}

/*
 * This is called for the directive LoadModule and actually loads
 * a shared object file into the address space of the server process.
 */

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
                          cmd->pool, "module %s is already loaded, skipping",
                          modname);
