    /* Second, check for actions (which override the method scripts) */
    action = r->handler ? r->handler :
        ap_field_noparam(r->pool, r->content_type);

    if (action && (t = apr_table_get(conf->action_types, action))) {
        if (*t++ == '0' && r->finfo.filetype == APR_NOFILE) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "File does not exist: %s", r->filename);
            return HTTP_NOT_FOUND;
        }

        script = t;
        /* propagate the handler name to the script
