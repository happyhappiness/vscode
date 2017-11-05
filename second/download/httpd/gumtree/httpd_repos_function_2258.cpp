static const char *
     set_dbd_cookie_remove(cmd_parms * parms, void *dconf, int flag)
{
    session_dbd_dir_conf *conf = dconf;

    conf->remove = flag;
    conf->remove_set = 1;

    return NULL;
}