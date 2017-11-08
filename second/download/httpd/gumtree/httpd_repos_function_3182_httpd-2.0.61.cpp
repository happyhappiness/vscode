static int apr_pool_is_child_of(apr_pool_t *pool, apr_pool_t *parent)
{
    if (parent == NULL)
        return 0;

    return apr_pool_walk_tree(parent, pool_is_child_of, pool);
}