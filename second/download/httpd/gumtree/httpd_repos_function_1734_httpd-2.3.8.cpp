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
        if (ival < 0)
            return "Retry must be a positive value";
        worker->retry = apr_time_from_sec(ival);
        worker->retry_set = 1;
    }
    else if (!strcasecmp(key, "ttl")) {
        /* Time in seconds that will destroy all the connections
         * that exceed the smax
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
        /* Acquire timeout in given unit (default is milliseconds).
         * If set this will be the maximum time to
         * wait for a free connection.
         */
        if (ap_timeout_parameter_parse(val, &timeout, "ms") != APR_SUCCESS)
            return "Acquire timeout has wrong format";
        if (timeout < 1000)
            return "Acquire must be at least one millisecond";
        worker->acquire = timeout;
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
        if (s < 512 && s) {
            return "IOBufferSize must be >= 512 bytes, or 0 for system default.";
        }
        worker->io_buffer_size = (s ? s : AP_IOBUFSIZE);
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
    else if (!strcasecmp(key, "disablereuse")) {
        if (!strcasecmp(val, "on"))
            worker->disablereuse = 1;
        else if (!strcasecmp(val, "off"))
            worker->disablereuse = 0;
        else
            return "DisableReuse must be On|Off";
        worker->disablereuse_set = 1;
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
    else if (!strcasecmp(key, "status")) {
        const char *v;
        int mode = 1;
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
            if (*v == 'D' || *v == 'd') {
                if (mode)
                    worker->status |= PROXY_WORKER_DISABLED;
                else
                    worker->status &= ~PROXY_WORKER_DISABLED;
            }
            else if (*v == 'S' || *v == 's') {
                if (mode)
                    worker->status |= PROXY_WORKER_STOPPED;
                else
                    worker->status &= ~PROXY_WORKER_STOPPED;
            }
            else if (*v == 'E' || *v == 'e') {
                if (mode)
                    worker->status |= PROXY_WORKER_IN_ERROR;
                else
                    worker->status &= ~PROXY_WORKER_IN_ERROR;
            }
            else if (*v == 'H' || *v == 'h') {
                if (mode)
                    worker->status |= PROXY_WORKER_HOT_STANDBY;
                else
                    worker->status &= ~PROXY_WORKER_HOT_STANDBY;
            }
            else if (*v == 'I' || *v == 'i') {
                if (mode)
                    worker->status |= PROXY_WORKER_IGNORE_ERRORS;
                else
                    worker->status &= ~PROXY_WORKER_IGNORE_ERRORS;
            }
            else {
                return "Unknown status parameter option";
            }
        }
    }
    else if (!strcasecmp(key, "flushpackets")) {
        if (!strcasecmp(val, "on"))
            worker->flush_packets = flush_on;
        else if (!strcasecmp(val, "off"))
            worker->flush_packets = flush_off;
        else if (!strcasecmp(val, "auto"))
            worker->flush_packets = flush_auto;
        else
            return "flushpackets must be on|off|auto";
    }
    else if (!strcasecmp(key, "flushwait")) {
        ival = atoi(val);
        if (ival > 1000 || ival < 0) {
            return "flushwait must be <= 1000, or 0 for system default of 10 millseconds.";
        }
        if (ival == 0)
            worker->flush_wait = PROXY_FLUSH_WAIT;
        else
            worker->flush_wait = ival * 1000;    /* change to microseconds */
    }
    else if (!strcasecmp(key, "ping")) {
        /* Ping/Pong timeout in given unit (default is second).
         */
        if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS)
            return "Ping/Pong timeout has wrong format";
        if (timeout < 1000)
            return "Ping/Pong timeout must be at least one millisecond";
        worker->ping_timeout = timeout;
        worker->ping_timeout_set = 1;
    }
    else if (!strcasecmp(key, "lbset")) {
        ival = atoi(val);
        if (ival < 0 || ival > 99)
            return "lbset must be between 0 and 99";
        worker->lbset = ival;
    }
    else if (!strcasecmp(key, "connectiontimeout")) {
        /* Request timeout in given unit (default is second).
         * Defaults to connection timeout
         */
        if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS)
            return "Connectiontimeout has wrong format";
        if (timeout < 1000)
            return "Connectiontimeout must be at least one millisecond.";
        worker->conn_timeout = timeout;
        worker->conn_timeout_set = 1;
    }
    else if (!strcasecmp(key, "flusher")) {
        worker->flusher = apr_pstrdup(p, val);
    }
    else {
        return "unknown Worker parameter";
    }
    return NULL;
}