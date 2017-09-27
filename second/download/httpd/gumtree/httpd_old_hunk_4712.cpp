            if (newfname && r->args && *r->args) {
                char *qs = strrchr(newfname, '?');
                if (qs && !strcmp(qs+1, r->args)) {
                    *qs = '\0';
                }
            }
        } else {
            fpm = 1;
        }

        if (newfname) {
            newfname = ap_strchr(newfname, '/');
            r->filename = newfname;
        }
    }

#if 0
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->filename: %s", (r->filename ? r->filename : "nil"));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->uri: %s", (r->uri ? r->uri : "nil"));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->path_info: %s", (r->path_info ? r->path_info : "nil"));
#endif

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    if (fpm || apr_table_get(r->notes, "virtual_script")) {
        /*
         * Adjust SCRIPT_NAME, PATH_INFO and PATH_TRANSLATED for PHP-FPM
         * TODO: Right now, PATH_INFO and PATH_TRANSLATED look OK...
         */
        const char *pend;
        const char *script_name = apr_table_get(r->subprocess_env, "SCRIPT_NAME");
        pend = script_name + strlen(script_name);
        if (r->path_info && *r->path_info) {
            pend = script_name + ap_find_path_info(script_name, r->path_info) - 1;
        }
        while (pend != script_name && *pend != '/') {
            pend--;
        }
        apr_table_setn(r->subprocess_env, "SCRIPT_NAME", pend);
        ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                      "fpm:virtual_script: Modified SCRIPT_NAME to: %s",
                      pend);
    }

    /* XXX are there any FastCGI specific env vars we need to send? */

    /* Give admins final option to fine-tune env vars */
    fix_cgivars(r, dconf);

    /* XXX mod_cgi/mod_cgid use ap_create_environment here, which fills in
