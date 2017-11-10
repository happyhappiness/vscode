static const char *set_max_ranges(cmd_parms *cmd, void *conf_, const char *arg)
{
    core_dir_config *conf = conf_;
    int val = 0;

    if (!strcasecmp(arg, "none")) {
        val = AP_MAXRANGES_NORANGES;
    }
    else if (!strcasecmp(arg, "default")) {
        val = AP_MAXRANGES_DEFAULT;
    }
    else if (!strcasecmp(arg, "unlimited")) {
        val = AP_MAXRANGES_UNLIMITED;
    }
    else {
        val = atoi(arg);
        if (val <= 0)
            return "MaxRanges requires 'none', 'default', 'unlimited' or "
                   "a positive integer";
    }

    conf->max_ranges = val;

    return NULL;
}