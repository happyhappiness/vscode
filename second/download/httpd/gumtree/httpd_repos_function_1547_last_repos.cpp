static const char *vhost_alias_set(cmd_parms *cmd, void *dummy, const char *map)
{
    mva_sconf_t *conf;
    mva_mode_e mode, *pmode;
    const char **pmap;
    const char *p;

    conf = (mva_sconf_t *) ap_get_module_config(cmd->server->module_config,
                                                &vhost_alias_module);
    /* there ought to be a better way of doing this */
    if (&vhost_alias_set_doc_root_ip == cmd->info) {
        mode = VHOST_ALIAS_IP;
        pmap = &conf->doc_root;
        pmode = &conf->doc_root_mode;
    }
    else if (&vhost_alias_set_cgi_root_ip == cmd->info) {
        mode = VHOST_ALIAS_IP;
        pmap = &conf->cgi_root;
        pmode = &conf->cgi_root_mode;
    }
    else if (&vhost_alias_set_doc_root_name == cmd->info) {
        mode = VHOST_ALIAS_NAME;
        pmap = &conf->doc_root;
        pmode = &conf->doc_root_mode;
    }
    else if (&vhost_alias_set_cgi_root_name == cmd->info) {
        mode = VHOST_ALIAS_NAME;
        pmap = &conf->cgi_root;
        pmode = &conf->cgi_root_mode;
    }
    else {
        return "INTERNAL ERROR: unknown command info";
    }

    if (!ap_os_is_path_absolute(cmd->pool, map)) {
        if (strcasecmp(map, "none")) {
            return "format string must be an absolute path, or 'none'";
        }
        *pmap = NULL;
        *pmode = VHOST_ALIAS_NONE;
        return NULL;
    }

    /* sanity check */
    p = map;
    while (*p != '\0') {
        if (*p++ != '%') {
            continue;
        }
        /* we just found a '%' */
        if (*p == 'p' || *p == '%') {
            ++p;
            continue;
        }
        /* optional dash */
        if (*p == '-') {
            ++p;
        }
        /* digit N */
        if (apr_isdigit(*p)) {
            ++p;
        }
        else {
            return "syntax error in format string";
        }
        /* optional plus */
        if (*p == '+') {
            ++p;
        }
        /* do we end here? */
        if (*p != '.') {
            continue;
        }
        ++p;
        /* optional dash */
        if (*p == '-') {
            ++p;
        }
        /* digit M */
        if (apr_isdigit(*p)) {
            ++p;
        }
        else {
            return "syntax error in format string";
        }
        /* optional plus */
        if (*p == '+') {
            ++p;
        }
    }
    *pmap = map;
    *pmode = mode;
    return NULL;
}