static const char *dav_cmd_davmintimeout(cmd_parms *cmd, void *config,
                                         const char *arg1)
{
    dav_dir_conf *conf = (dav_dir_conf *)config;

    conf->locktimeout = atoi(arg1);
    if (conf->locktimeout < 0)
        return "DAVMinTimeout requires a non-negative integer.";

    return NULL;
}