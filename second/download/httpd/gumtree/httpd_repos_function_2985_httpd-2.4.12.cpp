static const char *check_string(cmd_parms * cmd, const char *string)
{
    if (!string || !*string || ap_strchr_c(string, '=') || ap_strchr_c(string, '&')) {
        return apr_pstrcat(cmd->pool, cmd->directive->directive,
                           " cannot be empty, or contain '=' or '&'.",
                           NULL);
    }
    return NULL;
}