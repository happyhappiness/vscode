static void *dumpio_create_sconfig(apr_pool_t *p, server_rec *s)
{
    dumpio_conf_t *ptr = apr_pcalloc(p, sizeof *ptr);
    ptr->enable_input = 0;
    ptr->enable_output = 0;
    return ptr;
}