static const char *set_cookie_enable(cmd_parms *cmd, void *mconfig, int arg)
{
    cookie_dir_rec *dcfg = mconfig;

    dcfg->enabled = arg;
    return NULL;
}