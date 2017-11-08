static const char *cmd_log_message(cmd_parms *cmd, void *dconf_, const char *arg1,
                                   const char *arg2, const char *arg3)
{
    msg_entry *entry = apr_pcalloc(cmd->pool, sizeof(msg_entry));
    log_debug_dirconf *dconf = dconf_;
    int i, j;
    const char *err;
    const char *args[2];
    args[0] = arg2;
    args[1] = arg3;

    entry->msg_expr = ap_expr_parse_cmd(cmd, arg1, AP_EXPR_FLAG_STRING_RESULT|
                                                   AP_EXPR_FLAG_DONT_VARY,
                                        &err, NULL);
    if (err)
        return apr_psprintf(cmd->pool,
                            "Could not parse message expression '%s': %s",
                            arg1, err);

    for (i = 0; i < 2; i++) {
        if (args[i] == NULL)
            break;

        if (strncasecmp(args[i], "hook=", 5) == 0) {
            const char *name = args[i] + 5;
            j = 0;
            while (hooks[j]) {
                if (strcasecmp(hooks[j], name) == 0) {
                    entry->hook = hooks[j];
                    break;
                }
                j++;
            }
            if (entry->hook == NULL) {
                if (strcmp(name, "*") == 0 || strcasecmp(name, allhooks) == 0)
                    entry->hook = allhooks;
                else
                    return apr_psprintf(cmd->pool, "Invalid hook name: %s", name);
            }
        }
        else if (strncasecmp(args[i], "expr=", 5) == 0) {
            const char *expr = args[i] + 5;
            entry->condition = ap_expr_parse_cmd(cmd, expr,
                                                 AP_EXPR_FLAG_DONT_VARY,
                                                 &err, NULL);
            if (err)
                return apr_psprintf(cmd->pool,
                                    "Could not parse expression '%s': %s",
                                    expr, err);
        }
        else {
            return apr_psprintf(cmd->pool, "Invalid argument %s", args[i]);
        }
    }
    if (entry->hook == NULL)
        entry->hook = hooks[0];

    if (!dconf->entries)
        dconf->entries = apr_array_make(cmd->pool, 4, sizeof(msg_entry *));

    APR_ARRAY_PUSH(dconf->entries, msg_entry *) = entry;

    return NULL;
}