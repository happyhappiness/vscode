static const char *set_group_file(cmd_parms *cmd, void *config,
                                  const char *file)
{
    ((digest_config_rec *) config)->grpfile = file;
    return NULL;
}