         * logs a warning later
         */
        changed_limit_at_restart = 1;
        return NULL;
    }
    server_limit = tmp_server_limit;
    
    if (server_limit > MAX_SERVER_LIMIT) {
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    "WARNING: ServerLimit of %d exceeds compile time limit "
                    "of %d servers,", server_limit, MAX_SERVER_LIMIT);
       ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                    " lowering ServerLimit to %d.", MAX_SERVER_LIMIT);
       server_limit = MAX_SERVER_LIMIT;
    } 
    else if (server_limit < 1) {
	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "WARNING: Require ServerLimit > 0, setting to 1");
	server_limit = 1;
    }
    return NULL;
}

static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg) 
{
    int tmp_thread_limit;
    
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    tmp_thread_limit = atoi(arg);
