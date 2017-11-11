static int mime_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    const char *types_confname = ap_get_module_config(s->module_config,
                                                      &mime_module);
    apr_status_t status;

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

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *ll = l, *ct;

        if (l[0] == '#') {
            continue;
        }
        ct = ap_getword_conf(p, &ll);

        while (ll[0]) {
            char *ext = ap_getword_conf(p, &ll);
            ap_str_tolower(ext);
            apr_hash_set(mime_type_extensions, ext, APR_HASH_KEY_STRING, ct);
        }
    }
    ap_cfg_closefile(f);
    return OK;
}