        return apr_pstrcat(cmd->pool, "Invalid ScriptSock path",
                           arg, NULL);
    }

    return NULL;
}

static const command_rec cgid_cmds[] =
{
    AP_INIT_TAKE1("ScriptLog", set_scriptlog, NULL, RSRC_CONF,
                  "the name of a log for script debugging info"),
    AP_INIT_TAKE1("ScriptLogLength", set_scriptlog_length, NULL, RSRC_CONF,
                  "the maximum length (in bytes) of the script debug log"),
    AP_INIT_TAKE1("ScriptLogBuffer", set_scriptlog_buffer, NULL, RSRC_CONF,
                  "the maximum size (in bytes) to record of a POST request"),
    AP_INIT_TAKE1("ScriptSock", set_script_socket, NULL, RSRC_CONF,
                  "the name of the socket to use for communication with "
                  "the cgi daemon."),
    {NULL}
};

static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret,
                           apr_status_t rv, char *error)
{
