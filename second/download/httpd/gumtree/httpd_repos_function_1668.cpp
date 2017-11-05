static void *create_dir_config(apr_pool_t *p, char *dummy)
{
    serf_config_t *new = (serf_config_t *) apr_pcalloc(p, sizeof(serf_config_t));
    new->on = 0;
    new->preservehost = 1;
    return new;
}