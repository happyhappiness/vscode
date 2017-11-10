static const char *set_default_error_msg(cmd_parms *cmd, void *mconfig,
                                         const char *msg)
{
    include_dir_config *conf = mconfig;
    conf->default_error_msg = msg;

    return NULL;
}