static const char *set_worker_param(apr_pool_t *p,
                                    proxy_worker *worker,
                                    const char *key,
                                    const char *val)
{

    int ival;
    if (!strcasecmp(key, "loadfactor")) {
        /* Normalized load factor. Used with BalancerMamber,
         * it is a number between 1 and 100.
         */
        worker->lbfactor = atoi(val);
        if (worker->lbfactor < 1 || worker->lbfactor > 100)
            return "LoadFactor must be number between 1..100";
    }
    else if (!strcasecmp(key, "retry")) {
        /* If set it will give the retry timeout for the worker
         * The default value is 60 seconds, meaning that if
         * in error state, it will be retried after that timeout.
         */
        ival = atoi(val);
        if (ival < 1)
            return "Retry must be at least one second";
        worker->retry = apr_time_from_sec(ival);
    }
    else if (!strcasecmp(key, "ttl")) {
        /* Time in seconds that will destroy all the connections
         * that exced the smax
         */
        ival = atoi(val);
        if (ival < 1)
            return "TTL must be at least one second";
        worker->ttl = apr_time_from_sec(ival);
    }
    else if (!strcasecmp(key, "min")) {
        /* Initial number of connections to remote
         */
        ival = atoi(val);
        if (ival < 0)
            return "Min must be a positive number";
        worker->min = ival;
    }
    else if (!strcasecmp(key, "max")) {
        /* Maximum number of connections to remote
         */
        ival = atoi(val);
        if (ival < 0)
            return "Max must be a positive number";
        worker->hmax = ival;
    }
    /* XXX: More inteligent naming needed */
    else if (!strcasecmp(key, "smax")) {
        /* Maximum number of connections to remote that
         * will not be destroyed
         */
        ival = atoi(val);
        if (ival < 0)
            return "Smax must be a positive number";
        worker->smax = ival;
    }
    else if (!strcasecmp(key, "acquire")) {
        /* Acquire timeout in milliseconds.
         * If set this will be the maximum time to
         * wait for a free connection.
         */
        ival = atoi(val);
        if (ival < 1)
            return "Acquire must be at least one mili second";
        worker->acquire = apr_time_make(0, ival * 1000);
        worker->acquire_set = 1;
    }
    else if (!strcasecmp(key, "timeout")) {
        /* Connection timeout in seconds.
         * Defaults to server timeout.
         */
        ival = atoi(val);
        if (ival < 1)
            return "Timeout must be at least one second";
        worker->timeout = apr_time_from_sec(ival);
        worker->timeout_set = 1;
    }
    else if (!strcasecmp(key, "iobuffersize")) {
        long s = atol(val);
        worker->io_buffer_size = ((s > AP_IOBUFSIZE) ? s : AP_IOBUFSIZE);
        worker->io_buffer_size_set = 1;
    }
    else if (!strcasecmp(key, "receivebuffersize")) {
        ival = atoi(val);
        if (ival < 512 && ival != 0) {
            return "ReceiveBufferSize must be >= 512 bytes, or 0 for system default.";
        }
        worker->recv_buffer_size = ival;
        worker->recv_buffer_size_set = 1;
    }
    else if (!strcasecmp(key, "keepalive")) {
        if (!strcasecmp(val, "on"))
            worker->keepalive = 1;
        else if (!strcasecmp(val, "off"))
            worker->keepalive = 0;
        else
            return "KeepAlive must be On|Off";
        worker->keepalive_set = 1;
    }
    else if (!strcasecmp(key, "route")) {
        /* Worker route.
         */
        if (strlen(val) > PROXY_WORKER_MAX_ROUTE_SIZ)
            return "Route length must be < 64 characters";
        worker->route = apr_pstrdup(p, val);
    }
    else if (!strcasecmp(key, "redirect")) {
        /* Worker redirection route.
         */
        if (strlen(val) > PROXY_WORKER_MAX_ROUTE_SIZ)
            return "Redirect length must be < 64 characters";
        worker->redirect = apr_pstrdup(p, val);
    }