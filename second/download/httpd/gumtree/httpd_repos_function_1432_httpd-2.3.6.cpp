static void *create_mconfig_for_directory(apr_pool_t *p, char *dir)
{
    return mkconfig(p);
}