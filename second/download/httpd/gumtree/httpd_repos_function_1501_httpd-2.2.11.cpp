static const char *set_ftp_directory_charset(cmd_parms *cmd, void *dconf,
                                             const char *arg)
{
    proxy_dir_conf *conf = dconf;

    conf->ftp_directory_charset = arg;
    return NULL;
}