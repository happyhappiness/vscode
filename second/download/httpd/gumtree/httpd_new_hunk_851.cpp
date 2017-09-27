    }

    ap_threads_max_free = atoi(arg);
    return NULL;
}

static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_limit = atoi(arg);
    if (ap_threads_limit > HARD_THREAD_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: MaxThreads of %d exceeds compile time limit "
                    "of %d threads,", ap_threads_limit, HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " lowering MaxThreads to %d.  To increase, please "
                    "see the", HARD_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " HARD_THREAD_LIMIT define in %s.",
                    AP_MPM_HARD_LIMITS_FILE);
       ap_threads_limit = HARD_THREAD_LIMIT;
    }
    else if (ap_threads_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
            "WARNING: Require MaxThreads > 0, setting to 1");
        ap_threads_limit = 1;
    }
    return NULL;
}

static const command_rec netware_mpm_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("StartThreads", set_threads_to_start, NULL, RSRC_CONF,
              "Number of worker threads launched at server startup"),
AP_INIT_TAKE1("MinSpareThreads", set_min_free_threads, NULL, RSRC_CONF,
              "Minimum number of idle threads, to handle request spikes"),
AP_INIT_TAKE1("MaxSpareThreads", set_max_free_threads, NULL, RSRC_CONF,
