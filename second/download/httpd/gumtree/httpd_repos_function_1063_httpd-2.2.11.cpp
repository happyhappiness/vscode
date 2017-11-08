static const char *add_redirect_internal(cmd_parms *cmd,
                                         alias_dir_conf *dirconf,
                                         const char *arg1, const char *arg2,
                                         const char *arg3, int use_regex)
{
    alias_entry *new;
    server_rec *s = cmd->server;
    alias_server_conf *serverconf = ap_get_module_config(s->module_config,
                                                         &alias_module);
    int status = (int) (long) cmd->info;
    ap_regex_t *r = NULL;
    const char *f = arg2;
    const char *url = arg3;

    if (!strcasecmp(arg1, "gone"))
        status = HTTP_GONE;
    else if (!strcasecmp(arg1, "permanent"))
        status = HTTP_MOVED_PERMANENTLY;
    else if (!strcasecmp(arg1, "temp"))
        status = HTTP_MOVED_TEMPORARILY;
    else if (!strcasecmp(arg1, "seeother"))
        status = HTTP_SEE_OTHER;
    else if (apr_isdigit(*arg1))
        status = atoi(arg1);
    else {
        f = arg1;
        url = arg2;
    }

    if (use_regex) {
        r = ap_pregcomp(cmd->pool, f, AP_REG_EXTENDED);
        if (r == NULL)
            return "Regular expression could not be compiled.";
    }

    if (ap_is_HTTP_REDIRECT(status)) {
        if (!url)
            return "URL to redirect to is missing";
        /* PR#35314: we can allow path components here;
         * they get correctly resolved to full URLs.
         */
        if (!use_regex && !ap_is_url(url) && (url[0] != '/'))
            return "Redirect to non-URL";
    }
    else {
        if (url)
            return "Redirect URL not valid for this status";
    }

    if (cmd->path)
        new = apr_array_push(dirconf->redirects);
    else
        new = apr_array_push(serverconf->redirects);

    new->fake = f;
    new->real = url;
    new->regexp = r;
    new->redir_status = status;
    return NULL;
}