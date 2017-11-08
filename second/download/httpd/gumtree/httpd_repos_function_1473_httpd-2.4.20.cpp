static const char *configure_checkhandler(cmd_parms *cmd, void *d_, int arg)
{
    dir_config_rec *d = d_;

    d->checkhandler = arg ? MODDIR_ON : MODDIR_OFF;
    return NULL;
}