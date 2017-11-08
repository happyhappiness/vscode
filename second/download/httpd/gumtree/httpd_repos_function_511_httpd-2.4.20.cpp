static void *create_logio_dirconf (apr_pool_t *p, char *dummy)
{
    logio_dirconf_t *new =
        (logio_dirconf_t *) apr_pcalloc(p, sizeof(logio_dirconf_t));
    return (void *) new;
}