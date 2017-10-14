static const char *
    add_pass(cmd_parms *cmd, void *dummy, const char *arg, int is_regex)
{
    server_rec *s = cmd->server;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(s->module_config, &proxy_module);
    struct proxy_alias *new;
    char *f = cmd->path;
    char *r = NULL;
    char *word;
    apr_table_t *params = apr_table_make(cmd->pool, 5);
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    int i;
    int use_regex = is_regex;
    unsigned int flags = 0;

    while (*arg) {
        word = ap_getword_conf(cmd->pool, &arg);
        if (!f) {
            if (!strcmp(word, "~")) {
                if (is_regex) {
                    return "ProxyPassMatch invalid syntax ('~' usage).";
                }
                use_regex = 1;
                continue;
            }
            f = word;
        }
        else if (!r) {
            r = word;
        }
        else if (!strcasecmp(word,"nocanon")) {
            flags |= PROXYPASS_NOCANON;
        }
        else if (!strcasecmp(word,"interpolate")) {
            flags |= PROXYPASS_INTERPOLATE;
        }
        else {
            char *val = strchr(word, '=');
            if (!val) {
                if (cmd->path) {
                    if (*r == '/') {
                        return "ProxyPass|ProxyPassMatch can not have a path when defined in "
                               "a location.";
                    }
                    else {
                        return "Invalid ProxyPass|ProxyPassMatch parameter. Parameter must "
                               "be in the form 'key=value'.";
                    }
                }
                else {
                    return "Invalid ProxyPass|ProxyPassMatch parameter. Parameter must be "
                           "in the form 'key=value'.";
                }
            }
            else
                *val++ = '\0';
            apr_table_setn(params, word, val);
        }
    };

    if (r == NULL)
        return "ProxyPass|ProxyPassMatch needs a path when not defined in a location";

    new = apr_array_push(conf->aliases);
    new->fake = apr_pstrdup(cmd->pool, f);
    new->real = apr_pstrdup(cmd->pool, r);
    new->flags = flags;
    if (use_regex) {
        new->regex = ap_pregcomp(cmd->pool, f, AP_REG_EXTENDED);
        if (new->regex == NULL)
            return "Regular expression could not be compiled.";
    }
    else {
        new->regex = NULL;
    }

    if (r[0] == '!' && r[1] == '\0')
        return NULL;

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    /* Distinguish the balancer from worker */
    if (strncasecmp(r, "balancer:", 9) == 0) {
        proxy_balancer *balancer = ap_proxy_get_balancer(cmd->pool, conf, r);
        if (!balancer) {
            const char *err = ap_proxy_add_balancer(&balancer,
                                                    cmd->pool,
                                                    conf, r);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        for (i = 0; i < arr->nelts; i++) {
            const char *err = set_balancer_param(conf, cmd->pool, balancer, elts[i].key,
                                                 elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, conf, r);
        if (!worker) {
            const char *err = ap_proxy_add_worker(&worker, cmd->pool, conf, r);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        } else {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                         "worker %s already used by another worker", worker->name);
        }
        PROXY_COPY_CONF_PARAMS(worker, conf);

        for (i = 0; i < arr->nelts; i++) {
            const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                               elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
    }
    return NULL;
}