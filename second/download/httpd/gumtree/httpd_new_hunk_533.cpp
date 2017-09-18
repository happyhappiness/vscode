    if (!strcasecmp(signal_arg, "restart") 
            || !strcasecmp(signal_arg, "config")) {
        return OK;
    }

    if (ap_setup_listeners(s) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, 
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    if (!set_listeners_noninheritable(s->process->pool)) {
        return 1;
