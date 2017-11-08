static const char *set_flags(cmd_parms *cmd, void *CFG, const char *arg)
{
    proxy_html_conf *cfg = CFG;
    if (arg && *arg) {
        if (!strcasecmp(arg, "lowercase"))
            cfg->flags |= NORM_LC;
        else if (!strcasecmp(arg, "dospath"))
            cfg->flags |= NORM_MSSLASH;
        else if (!strcasecmp(arg, "reset"))
            cfg->flags |= NORM_RESET;
    }
    return NULL;
}