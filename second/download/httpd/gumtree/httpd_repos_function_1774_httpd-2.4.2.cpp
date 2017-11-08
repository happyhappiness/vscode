static const char *
    add_pass(cmd_parms *cmd, void *dummy, const char *arg, int is_regex)
{
    proxy_dir_conf *dconf = (proxy_dir_conf *)dummy;
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
    const char *err;

    err = ap_check_cmd_context(cmd, NOT_IN_DIRECTORY|NOT_IN_FILES);
    if (err) {
        return err;
    }

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
        else if (!strcasecmp(word,"noquery")) {
            flags |= PROXYPASS_NOQUERY;
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

    if (r == NULL) {
        return "ProxyPass|ProxyPassMatch needs a path when not defined in a location";
    }

    /* if per directory, save away the single alias */
    if (cmd->path) {
        dconf->alias = apr_pcalloc(cmd->pool, sizeof(struct proxy_alias));
        dconf->alias_set = 1;
        new = dconf->alias;
        if (apr_fnmatch_test(f)) {
            use_regex = 1;
        }
    }
    /* if per server, add to the alias array */
    else {
        new = apr_array_push(conf->aliases);
    }

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
    if (ap_proxy_valid_balancer_name(r, 9)) {
        proxy_balancer *balancer = ap_proxy_get_balancer(cmd->pool, conf, r, 0);
        if (!balancer) {
            const char *err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, r, f, 0);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        else {
            ap_proxy_update_balancer(cmd->pool, balancer, f);
        }
        for (i = 0; i < arr->nelts; i++) {
            const char *err = set_balancer_param(conf, cmd->pool, balancer, elts[i].key,
                                                 elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
        new->balancer = balancer;
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, NULL, conf, r);
        int reuse = 0;
        if (!worker) {
            const char *err = ap_proxy_define_worker(cmd->pool, &worker, NULL, conf, r, 0);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);

            PROXY_COPY_CONF_PARAMS(worker, conf);
        } else {
            reuse = 1;
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01145)
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         worker->s->name, new->real);
        }

        for (i = 0; i < arr->nelts; i++) {
            if (reuse) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01146)
                             "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                             elts[i].key, elts[i].val, worker->s->name);
            } else {
                const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                   elts[i].val);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            }
        }
    }
    return NULL;
}