static const char *add_member(cmd_parms *cmd, void *dummy, const char *arg)
{
    server_rec *s = cmd->server;
    proxy_server_conf *conf =
    ap_get_module_config(s->module_config, &proxy_module);
    proxy_balancer *balancer;
    proxy_worker *worker;
    char *path = cmd->path;
    char *name = NULL;
    char *word;
    apr_table_t *params = apr_table_make(cmd->pool, 5);
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    int reuse = 0;
    int i;
    /* XXX: Should this be NOT_IN_DIRECTORY|NOT_IN_FILES? */
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;

    if (cmd->path)
        path = apr_pstrdup(cmd->pool, cmd->path);

    while (*arg) {
        char *val;
        word = ap_getword_conf(cmd->pool, &arg);
        val = strchr(word, '=');

        if (!val) {
            if (!path)
                path = word;
            else if (!name)
                name = word;
            else {
                if (cmd->path)
                    return "BalancerMember can not have a balancer name when defined in a location";
                else
                    return "Invalid BalancerMember parameter. Parameter must "
                           "be in the form 'key=value'";
            }
        } else {
            *val++ = '\0';
            apr_table_setn(params, word, val);
        }
    }
    if (!path)
        return "BalancerMember must define balancer name when outside <Proxy > section";
    if (!name)
        return "BalancerMember must define remote proxy server";

    ap_str_tolower(path);   /* lowercase scheme://hostname */

    /* Try to find the balancer */
    balancer = ap_proxy_get_balancer(cmd->temp_pool, conf, path, 0);
    if (!balancer) {
        err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, path, "/", 0);
        if (err)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
    }

    /* Try to find existing worker */
    worker = ap_proxy_get_worker(cmd->temp_pool, balancer, conf, ap_proxy_de_socketfy(cmd->temp_pool, name));
    if (!worker) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01147)
                     "Defining worker '%s' for balancer '%s'",
                     name, balancer->s->name);
        if ((err = ap_proxy_define_worker(cmd->pool, &worker, balancer, conf, name, 0)) != NULL)
            return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01148)
                     "Defined worker '%s' for balancer '%s'",
                     ap_proxy_worker_name(cmd->pool, worker), balancer->s->name);
        PROXY_COPY_CONF_PARAMS(worker, conf);
    } else {
        reuse = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01149)
                     "Sharing worker '%s' instead of creating new worker '%s'",
                     ap_proxy_worker_name(cmd->pool, worker), name);
    }

    arr = apr_table_elts(params);
    elts = (const apr_table_entry_t *)arr->elts;
    for (i = 0; i < arr->nelts; i++) {
        if (reuse) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01150)
                         "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                         elts[i].key, elts[i].val, ap_proxy_worker_name(cmd->pool, worker));
        } else {
            err = set_worker_param(cmd->pool, worker, elts[i].key,
                                               elts[i].val);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
        }
    }

    return NULL;
}