static const char *check_string(cmd_parms * cmd, const char *string)
{
    if (APR_SUCCESS != ap_cookie_check_string(string)) {
        return apr_pstrcat(cmd->pool, cmd->directive->directive,
                           " cannot be empty, or contain '=', ';' or '&'.",
                           NULL);
    }
    return NULL;
}