static const char *set_worker_param(apr_pool_t *p,
                                    proxy_worker *worker,
                                    const char *key,
                                    const char *val)
{

    int ival;
    apr_interval_time_t timeout;

    if (!strcasecmp(key, "loadfactor")) {
        /* Normalized load factor. Used with BalancerMamber,
         * it is a number between 1 and 100.
         */
        worker->s->lbfactor = atoi(val);
        if (worker->s->lbfactor < 1 || worker->s->lbfactor > 100)
            return "LoadFactor must be a number between 1..100";
    }
    else if (!strcasecmp(key, "retry")) {
        /* If set it will give the retry timeout for the worker
         * The default value is 60 seconds, meaning that if
         * in error state, it will be retried after that timeout.
         */
        ival = atoi(val);
        if (ival < 0)
            return "Retry must be a positive value";
        worker->s->retry = apr_time_from_sec(ival);
        worker->s->retry_set = 1;
    }
    else if (!strcasecmp(key, "ttl")) {
        /* Time in seconds that will destroy all the connections
         * that exceed the smax
         */
        ival = atoi(val);
        if (ival < 1)
            return "TTL must be at least one second";
        worker->s->ttl = apr_time_from_sec(ival);
    }
    else if (!strcasecmp(key, "min")) {
        /* Initial number of connections to remote
         */
        ival = atoi(val);
        if (ival < 0)
            return "Min must be a positive number";
        worker->s->min = ival;
    }
    else if (!strcasecmp(key, "max")) {
        /* Maximum number of connections to remote
         */
        ival = atoi(val);
        if (ival < 0)
            return "Max must be a positive number";
        worker->s->hmax = ival;
    }
    /* XXX: More inteligent naming needed */
    else if (!strcasecmp(key, "smax")) {
        /* Maximum number of connections to remote that
         * will not be destroyed
         */
        ival = atoi(val);
        if (ival < 0)
            return "Smax must be a positive number";
        worker->s->smax = ival;
    }
    else if (!strcasecmp(key, "acquire")) {
        /* Acquire timeout in given unit (default is milliseconds).
         * If set this will be the maximum time to
         * wait for a free connection.
         */
        if (ap_timeout_parameter_parse(val, &timeout, "ms") != APR_SUCCESS)
            return "Acquire timeout has wrong format";
        if (timeout < 1000)
            return "Acquire must be at least one millisecond";
        worker->s->acquire = timeout;
        worker->s->acquire_set = 1;
    }
    else if (!strcasecmp(key, "timeout")) {
        /* Connection timeout in seconds.
         * Defaults to server timeout.
         */
        ival = atoi(val);
        if (ival < 1)
            return "Timeout must be at least one second";
        worker->s->timeout = apr_time_from_sec(ival);
        worker->s->timeout_set = 1;
    }
    else if (!strcasecmp(key, "iobuffersize")) {
        long s = atol(val);
        if (s < 512 && s) {
            return "IOBufferSize must be >= 512 bytes, or 0 for system default.";
        }
        worker->s->io_buffer_size = (s ? s : AP_IOBUFSIZE);
        worker->s->io_buffer_size_set = 1;
    }
    else if (!strcasecmp(key, "receivebuffersize")) {
        ival = atoi(val);
        if (ival < 512 && ival != 0) {
            return "ReceiveBufferSize must be >= 512 bytes, or 0 for system default.";
        }
        worker->s->recv_buffer_size = ival;
        worker->s->recv_buffer_size_set = 1;
    }
    else if (!strcasecmp(key, "keepalive")) {
        if (!strcasecmp(val, "on"))
            worker->s->keepalive = 1;
        else if (!strcasecmp(val, "off"))
            worker->s->keepalive = 0;
        else
            return "KeepAlive must be On|Off";
        worker->s->keepalive_set = 1;
    }
    else if (!strcasecmp(key, "disablereuse")) {
        if (!strcasecmp(val, "on"))
            worker->s->disablereuse = 1;
        else if (!strcasecmp(val, "off"