static const char *proxysection(cmd_parms *cmd, void *mconfig, const char *arg)
{
    const char *errmsg;
    const char *endp = ap_strrchr_c(arg, '>');
    int old_overrides = cmd->override;
    char *old_path = cmd->path;
    proxy_dir_conf *conf;
    ap_conf_vector_t *new_dir_conf = ap_create_per_dir_config(cmd->pool);
    ap_regex_t *r = NULL;
    const command_rec *thiscmd = cmd->cmd;
    char *word, *val;
    proxy_balancer *balancer = NULL;
    proxy_worker *worker = NULL;

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    proxy_server_conf *sconf =
    (proxy_server_conf *) ap_get_module_config(cmd->server->module_config, &proxy_module);

    if (err != NULL) {
        return err;
    }

    if (endp == NULL) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive missing closing '>'", NULL);
    }

    arg = apr_pstrndup(cmd->pool, arg, endp-arg);

    if (!arg) {
        if (thiscmd->cmd_data)
            return "<ProxyMatch > block must specify a path";
        else
            return "<Proxy > block must specify a path";
    }

    cmd->path = ap_getword_conf(cmd->pool, &arg);
    cmd->override = OR_ALL|ACCESS_CONF;

    if (!strncasecmp(cmd->path, "proxy:", 6))
        cmd->path += 6;

    /* XXX Ignore case?  What if we proxy a case-insensitive server?!?
     * While we are at it, shouldn't we also canonicalize the entire
     * scheme?  See proxy_fixup()
     */
    if (thiscmd->cmd_data) { /* <ProxyMatch> */
        r = ap_pregcomp(cmd->pool, cmd->path, AP_REG_EXTENDED);
        if (!r) {
            return "Regex could not be compiled";
        }
    }

    /* initialize our config and fetch it */
    conf = ap_set_config_vectors(cmd->server, new_dir_conf, cmd->path,
                                 &proxy_module, cmd->pool);

    errmsg = ap_walk_config(cmd->directive->first_child, cmd, new_dir_conf);
    if (errmsg != NULL)
        return errmsg;

    conf->r = r;
    conf->p = cmd->path;
    conf->p_is_fnmatch = apr_fnmatch_test(conf->p);

    if (r) {
        conf->refs = apr_array_make(cmd->pool, 8, sizeof(char *));
        ap_regname(r, conf->refs, AP_REG_MATCH, 1);
    }

    ap_add_per_proxy_conf(cmd->server, new_dir_conf);

    if (*arg != '\0') {
        if (thiscmd->cmd_data)
            return "Multiple <ProxyMatch> arguments not (yet) supported.";
        if (conf->p_is_fnmatch)
            return apr_pstrcat(cmd->pool, thiscmd->name,
                               "> arguments are not supported for wildchar url.",
                               NULL);
        if (!ap_strchr_c(conf->p, ':'))
            return apr_pstrcat(cmd->pool, thiscmd->name,
                               "> arguments are not supported for non url.",
                               NULL);
        if (ap_proxy_valid_balancer_name((char *)conf->p, 9)) {
            balancer = ap_proxy_get_balancer(cmd->pool, sconf, conf->p, 0);
            if (!balancer) {
                err = ap_proxy_define_balancer(cmd->pool, &balancer,
                                               sconf, conf->p, "/", 0);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, thiscmd->name,
                                       " ", err, NULL);
            }
        }
        else {
            worker = ap_proxy_get_worker(cmd->temp_pool, NULL, sconf,
                                         ap_proxy_de_socketfy(cmd->temp_pool, (char*)conf->p));
            if (!worker) {
                err = ap_proxy_define_worker(cmd->pool, &worker, NULL,
                                          sconf, conf->p, 0);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, thiscmd->name,
                                       " ", err, NULL);
            }
        }
        if (worker == NULL && balancer == NULL) {
            return apr_pstrcat(cmd->pool, thiscmd->name,
                               "> arguments are supported only for workers.",
                               NULL);
        }
        while (*arg) {
            word = ap_getword_conf(cmd->pool, &arg);
            val = strchr(word, '=');
            if (!val) {
                return "Invalid Proxy parameter. Parameter must be "
                       "in the form 'key=value'";
            }
            else
                *val++ = '\0';
            if (worker)
                err = set_worker_param(cmd->pool, worker, word, val);
            else
                err = set_balancer_param(sconf, cmd->pool, balancer,
                                         word, val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, thiscmd->name, " ", err, " ",
                                   word, "=", val, "; ", conf->p, NULL);
        }
    }

    cmd->path = old_path;
    cmd->override = old_overrides;

    return NULL;
}