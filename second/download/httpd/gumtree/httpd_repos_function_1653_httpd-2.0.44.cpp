static const char *set_digest_file(cmd_parms *cmd, void *config,
                                   const char *file)
{
    ((digest_config_rec *) config)->pwfile = file;
    return NULL;
}