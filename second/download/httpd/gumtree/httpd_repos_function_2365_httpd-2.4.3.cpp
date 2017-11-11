static const char *set_cookie_name2(cmd_parms * cmd, void *config, const char *args)
{
    char *last;
    char *line = apr_pstrdup(cmd->pool, args);
    session_dbd_dir_conf *conf = (session_dbd_dir_conf *) config;
    char *cookie = apr_strtok(line, " \t", &last);
    conf->name2 = cookie;
    conf->name2_set = 1;
    while (apr_isspace(*last)) {
        last++;
    }
    conf->name2_attrs = last;
    return check_string(cmd, cookie);
}