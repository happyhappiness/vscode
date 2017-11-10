static const char *set_worker_param(apr_pool_t *p,
                                    server_rec *s,
                                    proxy_worker *worker,
                                    const char *key,
                                    const char *val)
{

    int ival;
    apr_interval_time_t timeout;

    if (!strcasecmp(key, "loadfactor")) {
        /* Normalized load factor. Used with BalancerMember,
         * it is a number between 1 and 100.
         */
        ival = atoi(val);
        if (ival < 1 || ival > 100)
            return "LoadFactor must be a number between 1..100";
        worker->s->lbfactor = ival;
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
        else if (!strcasecmp(val, "off"))
            worker->s->disablereuse = 0;
        else
            return "DisableReuse must be On|Off";
        worker->s->disablereuse_set = 1;
    }
    else if (!strcasecmp(key, "enablereuse")) {
        if (!strcasecmp(val, "on"))
            worker->s->disablereuse = 0;
        else if (!strcasecmp(val, "off"))
            worker->s->disablereuse = 1;
        else
            return "EnableReuse must be On|Off";
        worker->s->disablereuse_set = 1;
    }
    else if (!strcasecmp(key, "route")) {
        /* Worker route.
         */
        if (strlen(val) >= sizeof(worker->s->route))
            return apr_psprintf(p, "Route length must be < %d characters",
                    (int)sizeof(worker->s->route));
        PROXY_STRNCPY(worker->s->route, val);
    }
    else if (!strcasecmp(key, "redirect")) {
        /* Worker redirection route.
         */
        if (strlen(val) >= sizeof(worker->s->redirect))
            return apr_psprintf(p, "Redirect length must be < %d characters",
                    (int)sizeof(worker->s->redirect));
        PROXY_STRNCPY(worker->s->redirect, val);
    }
    else if (!strcasecmp(key, "status")) {
        const char *v;
        int mode = 1;
        apr_status_t rv;
        /* Worker status.
         */
        for (v = val; *v; v++) {
            if (*v == '+') {
                mode = 1;
                v++;
            }
            else if (*v == '-') {
                mode = 0;
                v++;
            }
            rv = ap_proxy_set_wstatus(*v, mode, worker);
            if (rv != APR_SUCCESS)
                return "Unknown status parameter option";
        }
    }
    else if (!strcasecmp(key, "flushpackets")) {
        if (!strcasecmp(val, "on"))
            worker->s->flush_packets = flush_on;
        else if (!strcasecmp(val, "off"))
            worker->s->flush_packets = flush_off;
        else if (!strcasecmp(val, "auto"))
            worker->s->flush_packets = flush_auto;
        else
            return "flushpackets must be on|off|auto";
    }
    else if (!strcasecmp(key, "flushwait")) {
        ival = atoi(val);
        if (ival > 1000 || ival < 0) {
            return "flushwait must be <= 1000, or 0 for system default of 10 millseconds.";
        }
        if (ival == 0)
            worker->s->flush_wait = PROXY_FLUSH_WAIT;
        else
            worker->s->flush_wait = ival * 1000;    /* change to microseconds */
    }
    else if (!strcasecmp(key, "ping")) {
        /* Ping/Pong timeout in given unit (default is second).
         */
        if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS)
            return "Ping/Pong timeout has wrong format";
        if (timeout < 1000)
            return "Ping/Pong timeout must be at least one millisecond";
        worker->s->ping_timeout = timeout;
        worker->s->ping_timeout_set = 1;
    }
    else if (!strcasecmp(key, "lbset")) {
        ival = atoi(val);
        if (ival < 0 || ival > 99)
            return "lbset must be between 0 and 99";
        worker->s->lbset = ival;
    }
    else if (!strcasecmp(key, "connectiontimeout")) {
        /* Request timeout in given unit (default is second).
         * Defaults to connection timeout
         */
        if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS)
            return "Connectiontimeout has wrong format";
        if (timeout < 1000)
            return "Connectiontimeout must be at least one millisecond.";
        worker->s->conn_timeout = timeout;
        worker->s->conn_timeout_set = 1;
    }
    else if (!strcasecmp(key, "flusher")) {
        if (strlen(val) >= sizeof(worker->s->flusher))
            apr_psprintf(p, "flusher name length must be < %d characters",
                    (int)sizeof(worker->s->flusher));
        PROXY_STRNCPY(worker->s->flusher, val);
    }
    else {
        if (set_worker_hc_param_f) {
            return set_worker_hc_param_f(p, s, worker, key, val, NULL);
        } else {
            return "unknown Worker parameter";
        }
    }
    