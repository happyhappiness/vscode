static const char *
    set_proxy_param(cmd_parms *cmd, void *dummy, const char *arg)
{
    server_rec *s = cmd->server;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(s->module_config, &proxy_module);
    char *name = NULL;
    char *word, *val;
    proxy_balancer *balancer = NULL;
    proxy_worker *worker = NULL;
    int in_proxy_section = 0;
    /* XXX: Should this be NOT_IN_DIRECTORY|NOT_IN_FILES? */
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;

    if (cmd->directive->parent &&
        strncasecmp(cmd->directive->parent->directive,
                    "<Proxy", 6) == 0) {
        const char *pargs = cmd->directive->parent->args;
        /* Directive inside <Proxy section
         * Parent directive arg is the worker/balancer name.
         */
        name = ap_getword_conf(cmd->temp_pool, &pargs);
        if ((word = ap_strchr(name, '>')))
            *word = '\0';
        in_proxy_section = 1;
    }
    else {
        /* Standard set directive with worker/balancer
         * name as first param.
         */
        name = ap_getword_conf(cmd->temp_pool, &arg);
    }

    if (ap_proxy_valid_balancer_name(name, 9)) {
        balancer = ap_proxy_get_balancer(cmd->pool, conf, name, 0);
        if (!balancer) {
            if (in_proxy_section) {
                err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, name, "/", 0);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxySet ",
                                       err, NULL);
            }
            else
                return apr_pstrcat(cmd->temp_pool, "ProxySet can not find '",
                                   name, "' Balancer.", NULL);
        }
    }
    else {
        worker = ap_proxy_get_worker(cmd->temp_pool, NULL, conf, ap_proxy_de_socketfy(cmd->temp_pool, name));
        if (!worker) {
            if (in_proxy_section) {
                err = ap_proxy_define_worker(cmd->pool, &worker, NULL,
                                             conf, name, 0);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxySet ",
                                       err, NULL);
            }
            else
                return apr_pstrcat(cmd->temp_pool, "ProxySet can not find '",
                                   name, "' Worker.", NULL);
        }
    }

    while (*arg) {
        word = ap_getword_conf(cmd->pool, &arg);
        val = strchr(word, '=');
        if (!val) {
            return "Invalid ProxySet parameter. Parameter must be "
                   "in the form 'key=value'";
        }
        else
            *val++ = '\0';
        if (worker)
            err = set_worker_param(cmd->pool, cmd->server, worker, word, val);
        else
            err = set_balancer_param(conf, cmd->pool, balancer, word, val);

        if (err)
            return apr_pstrcat(cmd->temp_pool, "ProxySet: ", err, " ", word, "=", val, "; ", name, NULL);
    }

    return NULL;
}