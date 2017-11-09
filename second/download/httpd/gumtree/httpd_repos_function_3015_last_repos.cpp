static const char *set_events(cmd_parms *cmd, void *CFG, const char *arg)
{
    tattr *attr;
    proxy_html_conf *cfg = CFG;
    if (cfg->events == NULL)
        cfg->events = apr_array_make(cmd->pool, 20, sizeof(tattr));
    attr = apr_array_push(cfg->events);
    attr->val = arg;
    return NULL;
}