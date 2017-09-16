    char *code;

    time_t base;

    time_t additional;

    time_t expires;

    char age[20];



    if (is_HTTP_ERROR(r->status))       /* Don't add Expires headers to errors */

        return DECLINED;



    if (r->main != NULL)        /* Say no to subrequests */

        return DECLINED;



    if (r->finfo.st_mode == 0)  /* no file ? shame. */

        return DECLINED;



    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config, &expires_module);

    if (conf == NULL) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "internal error: %s", r->filename);

        return SERVER_ERROR;

    };



    if (conf->active != ACTIVE_ON)

        return DECLINED;

