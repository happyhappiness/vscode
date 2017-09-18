
    if (r->main != NULL)        /* Say no to subrequests */
        return DECLINED;

    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config, &expires_module);
    if (conf == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "internal error: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (conf->active != ACTIVE_ON)
        return DECLINED;
