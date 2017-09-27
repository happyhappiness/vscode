        return apr_pstrcat(cmd->pool, "Cannot load ", filename,
                          " into server: ",
                          apr_dso_error(handle, my_error, sizeof(my_error)),
                          NULL);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(01576)
                 "loaded file %s", filename);

    return NULL;
}

static module *ap_find_loaded_module_symbol(server_rec *s, const char *modname)
