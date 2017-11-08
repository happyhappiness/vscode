static const char *set_urlmap(cmd_parms *cmd, void *CFG, const char *args)
{
    proxy_html_conf *cfg = (proxy_html_conf *)CFG;
    urlmap *map;
    apr_pool_t *pool = cmd->pool;
    urlmap *newmap;
    const char *usage =
              "Usage: ProxyHTMLURLMap from-pattern to-pattern [flags] [cond]";
    const char *from;
    const char *to;
    const char *flags;
    const char *cond = NULL;
  
    if (from = ap_getword_conf(cmd->pool, &args), !from)
        return usage;
    if (to = ap_getword_conf(cmd->pool, &args), !to)
        return usage;
    flags = ap_getword_conf(cmd->pool, &args);
    if (flags && *flags)
        cond = ap_getword_conf(cmd->pool, &args);
    if (cond && !*cond)
        cond = NULL;

    /* the args look OK, so let's use them */
    newmap = apr_palloc(pool, sizeof(urlmap));
    newmap->next = NULL;
    if (cfg->map) {
        for (map = cfg->map; map->next; map = map->next);
        map->next = newmap;
    }
    else
        cfg->map = newmap;

    return comp_urlmap(cmd, newmap, from, to, flags, cond);
}