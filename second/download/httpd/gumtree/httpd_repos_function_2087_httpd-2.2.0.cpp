static const char *satisfy(cmd_parms *cmd, void *c_, const char *arg)
{
    core_dir_config *c = c_;
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
            c->satisfy[i] = satisfy;
        }
    }

    return NULL;
}