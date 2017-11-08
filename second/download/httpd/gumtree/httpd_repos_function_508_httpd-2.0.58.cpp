static const char *header_inout_cmd(cmd_parms *cmd, void *indirconf,
                              const char *action, const char *inhdr,
                              const char *value, const char* envclause)
{
    headers_conf *dirconf = indirconf;
    const char *condition_var = NULL;
    char *colon;
    char *hdr = apr_pstrdup(cmd->pool, inhdr);
    header_entry *new;
    apr_array_header_t *fixup = (cmd->info == &hdr_in)
        ? dirconf->fixup_in   : (cmd->info == &hdr_err)
        ? dirconf->fixup_err
        : dirconf->fixup_out;

    new = (header_entry *) apr_array_push(fixup);

    if (!strcasecmp(action, "set"))
        new->action = hdr_set;
    else if (!strcasecmp(action, "add"))
        new->action = hdr_add;
    else if (!strcasecmp(action, "append"))
        new->action = hdr_append;
    else if (!strcasecmp(action, "unset"))
        new->action = hdr_unset;
    else if (!strcasecmp(action, "echo"))
        new->action = hdr_echo;
    else
        return "first argument must be add, set, append, unset or echo.";

    if (new->action == hdr_unset) {
        if (value)
            return "header unset takes two arguments";
    }
    else if (new->action == hdr_echo) {
        regex_t *regex;
        if (value)
            return "Header echo takes two arguments";
        else if (cmd->info == &hdr_in)
            return "Header echo only valid on Header directive";
        else {
            regex = ap_pregcomp(cmd->pool, hdr, REG_EXTENDED | REG_NOSUB);
            if (regex == NULL) {
                return "Header echo regex could not be compiled";
            }
        }
        new->regex = regex;
    }
    else if (!value)
        return "header requires three arguments";

    /* Handle the envclause on Header */
    if (envclause != NULL) {
        if (strncasecmp(envclause, "env=", 4) != 0) {
            return "error: envclause should be in the form env=envar";
        }
        if ((envclause[4] == '\0')
            || ((envclause[4] == '!') && (envclause[5] == '\0'))) {
            return "error: missing environment variable name. envclause should be in the form env=envar ";
        }
        condition_var = apr_pstrdup(cmd->pool, &envclause[4]);
    }
    
    if ((colon = strchr(hdr, ':')))
        *colon = '\0';

    new->header = hdr;
    new->condition_var = condition_var;

    return parse_format_string(cmd->pool, new, value);
}