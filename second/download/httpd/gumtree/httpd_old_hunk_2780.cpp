    if (!types_confname) {
        types_confname = AP_TYPES_CONFIG_FILE;
    }

    types_confname = ap_server_root_relative(p, types_confname);
    if (!types_confname) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                     "Invalid mime types config path %s",
                     (const char *)ap_get_module_config(s->module_config,
                                                        &mime_module));
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if ((status = ap_pcfg_openfile(&f, ptemp, types_confname))
                != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                     "could not open mime types config file %s.",
                     types_confname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    mime_type_extensions = apr_hash_make(p);
