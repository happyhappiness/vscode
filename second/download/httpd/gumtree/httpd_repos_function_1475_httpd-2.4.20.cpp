static void *create_dir_config(apr_pool_t *p, char *dummy)
{
    dir_config_rec *new = apr_pcalloc(p, sizeof(dir_config_rec));

    new->index_names = NULL;
    new->do_slash = MODDIR_UNSET;
    new->checkhandler = MODDIR_UNSET;
    new->redirect_index = REDIRECT_UNSET;
    return (void *) new;
}