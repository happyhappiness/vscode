static const char *generate_error(cmd_parms *cmd, void *dummy,
                                  const char *arg)
{
    if (!arg || !*arg) {
        return "The Error directive was used with no message.";
    }

    if (*arg == '"' || *arg == '\'') { /* strip off quotes */
        apr_size_t len = strlen(arg);
        char last = *(arg + len - 1);

        if (*arg == last) {
            return apr_pstrndup(cmd->pool, arg + 1, len - 2);
        }
    }

    return arg;
}