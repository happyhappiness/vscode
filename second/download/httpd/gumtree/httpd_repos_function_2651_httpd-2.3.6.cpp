static const char *satisfy(cmd_parms *cmd, void *dv, const char *arg)
{
    access_compat_dir_conf *d = (access_compat_dir_conf *) dv;
    int satisfy = SATISFY_NOSPEC;
    int i;

    if (!strcasecmp(arg, "all")) {
        satisfy = SATISFY_ALL;
    }
    else if (!strcasecmp(arg, "any")) {
        satisfy = SATISFY_ANY;
    }
    else {
        return "Satisfy either 'any' or 'all'.";
    }

    for (i = 0; i < METHODS; ++i) {
        if (cmd->limited & (AP_METHOD_BIT << i)) {
            d->satisfy[i] = satisfy;
        }
    }

    return NULL;
}