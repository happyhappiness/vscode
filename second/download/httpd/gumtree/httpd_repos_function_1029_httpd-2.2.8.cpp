static const char *configure_slash(cmd_parms *cmd, void *d_, int arg)
{
    dir_config_rec *d = d_;

    d->do_slash = arg ? SLASH_ON : SLASH_OFF;
    return NULL;
}