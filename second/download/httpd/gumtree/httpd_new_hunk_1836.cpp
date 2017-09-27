    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_limit = atoi(arg);
    return NULL;
}

static const command_rec netware_mpm_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("StartThreads", set_threads_to_start, NULL, RSRC_CONF,
