static void *merge_proxy_ftp_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    proxy_ftp_dir_conf *new = (proxy_ftp_dir_conf *) apr_pcalloc(p, sizeof(proxy_ftp_dir_conf));
    proxy_ftp_dir_conf *add = (proxy_ftp_dir_conf *) addv;
    proxy_ftp_dir_conf *base = (proxy_ftp_dir_conf *) basev;

    /* Put these in the dir config so they work inside <Location> */
    new->ftp_list_on_wildcard = add->ftp_list_on_wildcard_set ?
                                add->ftp_list_on_wildcard :
                                base->ftp_list_on_wildcard;
    new->ftp_list_on_wildcard_set = add->ftp_list_on_wildcard_set ?
                                1 :
                                base->ftp_list_on_wildcard_set;
    new->ftp_escape_wildcards = add->ftp_escape_wildcards_set ?
                                add->ftp_escape_wildcards :
                                base->ftp_escape_wildcards;
    new->ftp_escape_wildcards_set = add->ftp_escape_wildcards_set ?
                                1 :
                                base->ftp_escape_wildcards_set;
    new->ftp_directory_charset = add->ftp_directory_charset ?
                                 add->ftp_directory_charset :
                                 base->ftp_directory_charset;
    return new;
}