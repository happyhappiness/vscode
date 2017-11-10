static int pool_find(apr_pool_t *pool, void *data)
{
    void **pmem = (void **)data;
    debug_node_t *node;
    apr_uint32_t index;

    node = pool->nodes;

    while (node) {
        for (index = 0; index < node->index; index++) {
             if (node->beginp[index] <= *pmem
                 && node->endp[index] > *pmem) {
                 *pmem = pool;
                 return 1;
             }
        }

        node = node->next;
    }

    return 0;
}