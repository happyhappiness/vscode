static void *create_proxy_ftp_dir_config(apr_pool_t *p, char *dummy)
{
    proxy_ftp_dir_conf *new =
        (proxy_ftp_dir_conf *) apr_pcalloc(p, sizeof(proxy_ftp_dir_conf));

    /* Put these in the dir config so they work inside <Location> */
    new->ftp_list_on_wildcard = 1;
    new->ftp_escape_wildcards = 1;

    return (void *) new;
}