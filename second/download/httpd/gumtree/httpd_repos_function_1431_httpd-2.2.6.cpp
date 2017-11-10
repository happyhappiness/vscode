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
    else if (!strcasecmp(key, "lbset")) {
        ival = atoi(val);
        if (ival < 0 || ival > 99)
            return "lbset must be between 0 and 99";
        worker->lbset = ival;
    }
    else if (!strcasecmp(key, "ping")) {
        /* Ping/Pong timeout in seconds.
         */
        ival = atoi(val);
        if (ival < 1)
            return "Ping/Pong timeout must be at least one second";
        worker->ping_timeout = apr_time_from_sec(ival);
        worker->ping_timeout_set = 1;
    }
    else {
        return "unknown Worker parameter";
    }
    return NULL;
}