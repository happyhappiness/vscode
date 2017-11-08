static const char *set_default_time_fmt(cmd_parms *cmd, void *mconfig,
                                        const char *fmt)
{
    include_dir_config *conf = mconfig;
    conf->default_time_fmt = fmt;

    return NULL;
}