	return apr_pstrcat(cmd->pool, "Cannot load ", filename, 
			  " into server: ", 
			  apr_dso_error(handle, my_error, sizeof(my_error)),
			  NULL);
    }
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, NULL,
		 "loaded file %s", filename);

    return NULL;
}

#else /* not NO_DLOPEN */

static const char *load_file(cmd_parms *cmd, void *dummy, const char *filename)
{
    ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, cmd->pool, 
                 "WARNING: LoadFile not supported on this platform");
    return NULL;
}

static const char *load_module(cmd_parms *cmd, void *dummy, 
	                       const char *modname, const char *filename)
{
    ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, cmd->pool, 
                 "WARNING: LoadModule not supported on this platform");
    return NULL;
}

#endif /* NO_DLOPEN */

