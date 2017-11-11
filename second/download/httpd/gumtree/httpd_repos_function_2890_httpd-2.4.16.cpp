static const char *all_parse_config(cmd_parms *cmd, const char *require_line,
                                    const void **parsed_require_line)
{
    /*
     * If the argument to the 'all' provider is 'granted' then just let
     * everybody in. This would be equivalent to the previous syntax of
     * 'allow from all'. If the argument is 'denied' we reject everbody,
     * which is equivalent to 'deny from all'.
     */
    if (strcasecmp(require_line, "granted") == 0) {
        *parsed_require_line = (void *)1;
        return NULL;
    }
    else if (strcasecmp(require_line, "denied") == 0) {
        /* *parsed_require_line is already NULL */
        return NULL;
    }
    else {
        return "Argument for 'Require all' must be 'granted' or 'denied'";
    }
}