static const char *set_ftp_list_on_wildcard(cmd_parms *cmd, void *dconf,
                                            int flag)
{
    proxy_ftp_dir_conf *conf = dconf;

    conf->ftp_list_on_wildcard = flag;
    conf->ftp_list_on_wildcard_set = 1;
    return NULL;
}