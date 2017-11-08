static int pool_is_child_of(apr_pool_t *parent, void *data)
{
    apr_pool_t *pool = (apr_pool_t *)data;

    return (pool == parent);
}