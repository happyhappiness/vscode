static void *create_dir_expires_config(apr_pool_t *p, char *dummy)
{
    expires_dir_config *new =
    (expires_dir_config *) apr_pcalloc(p, sizeof(expires_dir_config));
    new->active = ACTIVE_DONTCARE;
    new->expiresdefault = "";
    new->expiresbytype = apr_table_make(p, 4);
    return (void *) new;
}