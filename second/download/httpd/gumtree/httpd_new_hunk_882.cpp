         * logs a warning later
         */
        changed_limit_at_restart = 1;
        return NULL;
    }
    thread_limit = tmp_thread_limit;

    if (thread_limit > MAX_THREAD_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    "WARNING: ThreadLimit of %d exceeds compile time limit "
                    "of %d threads,", thread_limit, MAX_THREAD_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                    " lowering ThreadLimit to %d.", MAX_THREAD_LIMIT);
       thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: Require ThreadLimit > 0, setting to 1");
	thread_limit = 1;
    }
    return NULL;
}
static const char *set_disable_acceptex(cmd_parms *cmd, void *dummy, char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    if (use_acceptex) {
        use_acceptex = 0;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL,
                     "Disabled use of AcceptEx() WinSock2 API");
    }
    return NULL;
}

static const command_rec winnt_cmds[] = {
