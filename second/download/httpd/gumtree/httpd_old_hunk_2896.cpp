#endif
    magic_server_config_rec *conf = (magic_server_config_rec *)
                    ap_get_module_config(s->module_config, &mime_magic_module);
    const char *fname = ap_server_root_relative(p, conf->magicfile);

    if (!fname) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                     MODNAME ": Invalid magic file path %s", conf->magicfile);
        return -1;
    }
    if ((result = apr_file_open(&f, fname, APR_READ | APR_BUFFERED,
                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                     MODNAME ": can't read magic file %s", fname);
        return -1;
    }

    /* set up the magic list (empty) */
    conf->magic = conf->last = NULL;
