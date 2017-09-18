
        return apr_pstrcat(cmd->pool, "Cannot load ", szModuleFile,
			  " into server: ",
			  apr_dso_error(modhandle, my_error, sizeof(my_error)),
			  NULL);
    }
    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, cmd->pool,
		 "loaded module %s", modname);

    /*
     * Retrieve the pointer to the module structure through the module name:
     * First with the hidden variant (prefix `AP_') and then with the plain
     * symbol name.
