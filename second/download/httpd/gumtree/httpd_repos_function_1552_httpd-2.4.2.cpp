static const char *set_script_socket(cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    /* Make sure the pid is appended to the sockname */
    sockname = ap_append_pid(cmd->pool, arg, ".");
    sockname = ap_server_root_relative(cmd->pool, sockname);

    if (!sockname) {
        return apr_pstrcat(cmd->pool, "Invalid ScriptSock path",
                           arg, NULL);
    }

    return NULL;
}