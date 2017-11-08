static const char *set_balancer_param(proxy_server_conf *conf,
                                      apr_pool_t *p,
                                      proxy_balancer *balancer,
                                      const char *key,
                                      const char *val)
{

    int ival;
    if (!strcasecmp(key, "stickysession")) {
        char *path;
        /* Balancer sticky session name.
         * Set to something like JSESSIONID or
         * PHPSESSIONID, etc..,
         */
        if (strlen(val) >= sizeof(balancer->s->sticky_path))
            apr_psprintf(p, "stickysession length must be < %d characters",
                    (int)sizeof(balancer->s->sticky_path));
        PROXY_STRNCPY(balancer->s->sticky_path, val);
        PROXY_STRNCPY(balancer->s->sticky, val);

        if ((path = strchr((char *)balancer->s->sticky, '|'))) {
            *path++ = '\0';
            PROXY_STRNCPY(balancer->s->sticky_path, path);
        }
    }
    else if (!strcasecmp(key, "stickysessionsep")) {
        /* separator/delimiter for sessionid and route,
         * normally '.'
         */
        if (strlen(val) != 1) {
            if (!strcasecmp(val, "off"))
                balancer->s->sticky_separator = 0;
            else      
                return "stickysessionsep must be a single character or Off";
        }
        else
            balancer->s->sticky_separator = *val;
    }
    else if (!strcasecmp(key, "nofailover")) {
        /* If set to 'on' the session will break
         * if the worker is in error state or
         * disabled.
         */
        if (!strcasecmp(val, "on"))
            balancer->s->sticky_force = 1;
        else if (!strcasecmp(val, "off"))
            balancer->s->sticky_force = 0;
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
        balancer->s->timeout = apr_time_from_sec(ival);
    }
    else if (!strcasecmp(key, "maxattempts")) {
        /* Maximum number of failover attempts before
         * giving up.
         */
        ival = atoi(val);
        if (ival < 0)
            return "maximum number of attempts must be a positive number";
        balancer->s->max_attempts = ival;
        balancer->s->max_attempts_set = 1;
    }
    else if (!strcasecmp(key, "lbmethod")) {
        proxy_balancer_method *provider;
        if (strlen(val) > (sizeof(balancer->s->lbpname)-1))
            return "unknown lbmethod";
        provider = ap_lookup_provider(PROXY_LBMETHOD, val, "0");
        if (provider) {
            balancer->lbmethod = provider;
            if (PROXY_STRNCPY(balancer->s->lbpname, val) == APR_SUCCESS) {
                return NULL;
            }
            else {
                return "lbmethod name too large";
            }
        }
        return "unknown lbmethod";
    }
    else if (!strcasecmp(key, "scolonpathdelim")) {
        /* If set to 'on' then ';' will also be
         * used as a session path separator/delim (ala
         * mod_jk)
         */
        if (!strcasecmp(val, "on"))
            balancer->s->scolonsep = 1;
        else if (!strcasecmp(val, "off"))
            balancer->s->scolonsep = 0;
        else
            return "scolonpathdelim must be On|Off";
    }
    else if (!strcasecmp(key, "failonstatus")) {
        char *val_split;
        char *status;
        char *tok_state;

        val_split = apr_pstrdup(p, val);

        balancer->errstatuses = apr_array_make(p, 1, sizeof(int));

        status = apr_strtok(val_split, ", ", &tok_state);
        while (status != NULL) {
            ival = atoi(status);
            if (ap_is_HTTP_VALID_RESPONSE(ival)) {
                *(int *)apr_array_push(balancer->errstatuses) = ival;
            }
            else {
                return "failonstatus must be one or more HTTP response codes";
            }
            status = apr_strtok(NULL, ", ", &tok_state);
        }

    }
    else if (!strcasecmp(key, "failontimeout")) {
        if (!strcasecmp(val, "on"))
            balancer->failontimeout = 1;
        else if (!strcasecmp(val, "off"))
            balancer->failontimeout = 0;
        else
            return "failontimeout must be On|Off";
    }
    else if (!strcasecmp(key, "nonce")) {
        if (!strcasecmp(val, "None")) {
            *balancer->s->nonce = '\0';
        }
        else {
            if (PROXY_STRNCPY(balancer->s->nonce, val) != APR_SUCCESS) {
                return "Provided nonce is too large";
            }
        }
    }
    else if (!strcasecmp(key, "growth")) {
        ival = atoi(val);
        if (ival < 1 || ival > 100)   /* arbitrary limit here */
            return "growth must be between 1 and 100";
        balancer->growth = ival;
    }
    else if (!strcasecmp(key, "forcerecovery")) {
        if (!strcasecmp(val, "on"))
            balancer->s->forcerecovery = 1;
        else if (!strcasecmp(val, "off"))
            balancer->s->forcerecovery = 0;
        else
            return "forcerecovery must be On|Off";
    }
    else {
        return "unknown Balancer parameter";
    }
    return NULL;
}