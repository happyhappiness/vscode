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
    const char *err;

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
    }
    else {
        /* Standard set directive with worker/balancer
         * name as first param.
         */
        name = ap_getword_conf(cmd->temp_pool, &arg);
    }

    if (strncasecmp(name, "balancer:", 9) == 0) {
        balancer = ap_proxy_get_balancer(cmd->pool, conf, name);
        if (!balancer) {
            return apr_pstrcat(cmd->temp_pool, "ProxySet can not find '",
                               name, "' Balancer.", NULL);
        }
    }
    else {
        worker = ap_proxy_get_worker(cmd->temp_pool, conf, name);
        if (!worker) {
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
            err = set_worker_param(cmd->pool, worker, word, val);
        else
            err = set_balancer_param(conf, cmd->pool, balancer, word, val);

        if (err)
            return apr_pstrcat(cmd->temp_pool, "ProxySet: ", err, " ", word, "=", val, "; ", name, NULL);
    }

    return NULL;
}