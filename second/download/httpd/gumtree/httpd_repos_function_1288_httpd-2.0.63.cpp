static void *merge_proxy_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    proxy_dir_conf *new = (proxy_dir_conf *) apr_pcalloc(p, sizeof(proxy_dir_conf));
    proxy_dir_conf *add = (proxy_dir_conf *) addv;
    proxy_dir_conf *base = (proxy_dir_conf *) basev;

    new->p = add->p;
    new->p_is_fnmatch = add->p_is_fnmatch;
    new->r = add->r;
    new->ftp_directory_charset = add->ftp_directory_charset ?
                                 add->ftp_directory_charset :
                                 base->ftp_directory_charset;
    return new;
}