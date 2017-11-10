static void *create_action_dir_config(apr_pool_t *p, char *dummy)
{
    action_dir_config *new =
    (action_dir_config *) apr_pcalloc(p, sizeof(action_dir_config));

    new->action_types = apr_table_make(p, 4);

    return new;
}