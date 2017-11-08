static const char *set_cookie_name(cmd_parms * cmd, void *config,
                                   const char *args)
{
    char *last;
    char *line = apr_pstrdup(cmd->pool, args);
    session_cookie_dir_conf *conf = (session_cookie_dir_conf *) config;
    char *cookie = apr_strtok(line, " \t", &last);
    conf->name = cookie;
    conf->name_set = 1;
    while (apr_isspace(*last)) {
        last++;
    }
    conf->name_attrs = last;
    return check_string(cmd, cookie);
}