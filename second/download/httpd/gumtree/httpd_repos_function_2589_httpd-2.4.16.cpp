static const char *
     set_dbd_peruser(cmd_parms * parms, void *dconf, int flag)
{
    session_dbd_dir_conf *conf = dconf;

    conf->peruser = flag;
    conf->peruser_set = 1;

    return NULL;
}