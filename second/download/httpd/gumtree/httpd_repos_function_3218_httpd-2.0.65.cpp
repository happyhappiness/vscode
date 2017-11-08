static void *pool_alloc(apr_pool_t *pool, apr_size_t size)
{
    debug_node_t *node;
    void *mem;

    if ((mem = malloc(size)) == NULL) {
        if (pool->abort_fn)
            pool->abort_fn(APR_ENOMEM);

        return NULL;
    }

    node = pool->nodes;
    if (node == NULL || node->index == 64) {
        if ((node = malloc(SIZEOF_DEBUG_NODE_T)) == NULL) {
            if (pool->abort_fn)
                pool->abort_fn(APR_ENOMEM);

            return NULL;
        }

        memset(node, 0, SIZEOF_DEBUG_NODE_T);

        node->next = pool->nodes;
        pool->nodes = node;
        node->index = 0;
    }

    node->beginp[node->index] = mem;
    node->endp[node->index] = (char *)mem + size;
    node->index++;

    pool->stat_alloc++;
    pool->stat_total_alloc++;

    return mem;
}