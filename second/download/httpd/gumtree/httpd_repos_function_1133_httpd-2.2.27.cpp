static void *create_userdir_config(apr_pool_t *p, server_rec *s)
{
    userdir_config *newcfg = apr_pcalloc(p, sizeof(*newcfg));

    newcfg->globally_disabled = O_DEFAULT;
    newcfg->userdir = DEFAULT_USER_DIR;
    newcfg->enabled_users = apr_table_make(p, 4);
    newcfg->disabled_users = apr_table_make(p, 4);

    return newcfg;
}