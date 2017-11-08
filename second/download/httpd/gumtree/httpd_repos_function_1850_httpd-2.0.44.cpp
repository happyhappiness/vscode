static const char *satisfy(cmd_parms *cmd, void *c_, const char *arg)
{
    core_dir_config *c = c_;

    if (!strcasecmp(arg, "all")) {
        c->satisfy = SATISFY_ALL;
    }
    else if (!strcasecmp(arg, "any")) {
        c->satisfy = SATISFY_ANY;
    }
    else {
        return "Satisfy either 'any' or 'all'.";
    }

    return NULL;
}