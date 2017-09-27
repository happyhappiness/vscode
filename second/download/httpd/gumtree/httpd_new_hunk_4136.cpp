
    /* Check for overrides with ForceType / SetHandler
     */
    if (conf->mime_type && strcmp(conf->mime_type, "none"))
        ap_set_content_type(r, (char*) conf->mime_type);

    if (conf->expr_handler) { 
        const char *err;
        const char *val;
        val = ap_expr_str_exec(r, conf->expr_handler, &err);
        if (err) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03154)
                          "Can't evaluate handler expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        if (val != ap_strstr_c(val, "proxy:unix")) { 
            /* Retained for compatibility --  but not for UDS */
            char *tmp = apr_pstrdup(r->pool, val);
            ap_str_tolower(tmp);
            val = tmp;
        }

        if (strcmp(val, "none")) { 
            r->handler = val;
        }
    }
    else if (conf->handler && strcmp(conf->handler, "none")) { 
        r->handler = conf->handler;
    }

    /* Deal with the poor soul who is trying to force path_info to be
     * accepted within the core_handler, where they will let the subreq
     * address its contents.  This is toggled by the user in the very
     * beginning of the fixup phase (here!), so modules should override the user's
     * discretion in their own module fixup phase.  It is tristate, if
