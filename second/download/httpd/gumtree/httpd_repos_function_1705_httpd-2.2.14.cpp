static void *create_charset_dir_conf(apr_pool_t *p,char *dummy)
{
    charset_dir_t *dc = (charset_dir_t *)apr_pcalloc(p,sizeof(charset_dir_t));

    dc->debug = -1;
    return dc;
}