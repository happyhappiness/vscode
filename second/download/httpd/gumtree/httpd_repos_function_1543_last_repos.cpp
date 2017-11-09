static int action_handler(request_rec *r)
{
    action_dir_config *conf = (action_dir_config *)
        ap_get_module_config(r->per_dir_config, &actions_module);
    const char *t, *action;
    const char *script;
    int i;

    if (!conf->configured) {
        return DECLINED;
    }

    /* Note that this handler handles _all_ types, so handler is unchecked */

    /* Set allowed stuff */
    for (i = 0; i < METHODS; ++i) {
        if (conf->scripted[i])
            r->allowed |= (AP_METHOD_BIT << i);
    }

    /* First, check for the method-handling scripts */
    if (r->method_number == M_GET) {
        if (r->args)
            script = conf->scripted[M_GET];
        else
            script = NULL;
    }
    else {
        script = conf->scripted[r->method_number];
    }

    /* Check for looping, which can happen if the CGI script isn't */
    if (script && r->prev && r->prev->prev)
        return DECLINED;

    /* Second, check for actions (which override the method scripts) */
    action = r->handler ? r->handler :
        ap_field_noparam(r->pool, r->content_type);

    if (action && (t = apr_table_get(conf->action_types, action))) {
        int virtual = (*t++ == '0' ? 0 : 1);
        if (!virtual && r->finfo.filetype == APR_NOFILE) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00652)
                          "File does not exist: %s", r->filename);
            return HTTP_NOT_FOUND;
        }

        script = t;
        /* propagate the handler name to the script
         * (will be REDIRECT_HANDLER there)
         */
        apr_table_setn(r->subprocess_env, "HANDLER", action);
        if (virtual) {
            apr_table_setn(r->notes, "virtual_script", "1");
        }
    }

    if (script == NULL)
        return DECLINED;

    ap_internal_redirect_handler(apr_pstrcat(r->pool, script,
                                             ap_escape_uri(r->pool, r->uri),
                                             r->args ? "?" : NULL,
                                             r->args, NULL), r);
    return OK;
}