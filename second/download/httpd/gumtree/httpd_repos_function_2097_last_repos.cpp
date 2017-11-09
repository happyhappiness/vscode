static const char *set_ftp_escape_wildcards(cmd_parms *cmd, void *dconf,
                                            int flag)
{
    proxy_ftp_dir_conf *conf = dconf;

    conf->ftp_escape_wildcards = flag;
    conf->ftp_escape_wildcards_set = 1;
    return NULL;
}