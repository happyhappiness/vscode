static const char *set_undefined_echo(cmd_parms *cmd, void *mconfig,
                                      const char *msg)
{
    include_dir_config *conf = mconfig;
    conf->undefined_echo = msg;

    return NULL;
}