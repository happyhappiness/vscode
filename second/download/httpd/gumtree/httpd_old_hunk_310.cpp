	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: Require ThreadLimit > 0, setting to 1");
	thread_limit = 1;
    }
    return NULL;
}

static const command_rec winnt_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF,
  "Number of threads each child creates" ),
AP_INIT_TAKE1("ThreadLimit", set_thread_limit, NULL, RSRC_CONF,
  "Maximum worker threads in a server for this run of Apache"),
{ NULL }
};


/*
 * Signalling Apache on NT.
