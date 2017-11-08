static const char *add_options(cmd_parms *cmd, void *in_dc,
                               const char *arg)
{
    ef_dir_t *dc = in_dc;

    if (!strncasecmp(arg, "DebugLevel=", 11)) {
        dc->debug = atoi(arg + 11);
    }
    else if (!strcasecmp(arg, "LogStderr")) {
        dc->log_stderr = 1;
    }
    else if (!strcasecmp(arg, "NoLogStderr")) {
        dc->log_stderr = 0;
    }
    else {
        return apr_pstrcat(cmd->temp_pool,
                           "Invalid ExtFilterOptions option: ",
                           arg,
                           NULL);
    }

    return NULL;
}