static const char *set_balancer_param(proxy_server_conf *conf,
                                      apr_pool_t *p,
                                      proxy_balancer *balancer,
                                      const char *key,
                                      const char *val)
{

    int ival;
    if (!strcasecmp(key, "stickysession")) {
        /* Balancer sticky session name.
         * Set to something like JSESSIONID or
         * PHPSESSIONID, etc..,
         */
        balancer->sticky = apr_pstrdup(p, val);
    }
    else if (!strcasecmp(key, "nofailover")) {
        /* If set to 'on' the session will break
         * if the worker is in error state or
         * disabled.
         */
        if (!strcasecmp(val, "on"))
            balancer->sticky_force = 1;
        else if (!strcasecmp(val, "off"))
            balancer->sticky_force = 0;
        else
            return "failover must be On|Off";
    }
    else if (!strcasecmp(key, "timeout")) {
        /* Balancer timeout in seconds.
         * If set this will be the maximum time to
         * wait for a free worker.
         * Default is not to wait.
         */
        ival = atoi(val);
        if (ival < 1)
            return "timeout must be at least one second";
        balancer->timeout = apr_time_from_sec(ival);
    }
    else if (!strcasecmp(key, "maxattempts")) {
        /* Maximum number of failover attempts before
         * giving up.
         */
        ival = atoi(val);
        if (ival < 0)
            return "maximum number of attempts must be a positive number";
        balancer->max_attempts = ival;
        balancer->max_attempts_set = 1;
    }
    else if (!strcasecmp(key, "lbmethod")) {
        proxy_balancer_method *provider;
        provider = ap_lookup_provider(PROXY_LBMETHOD, val, "0");
        if (provider) {
            balancer->lbmethod = provider;
            return NULL;
        }
        return "unknown lbmethod";
    }
    else {
        return "unknown Balancer parameter";
    }
    return NULL;
}