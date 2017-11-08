static int pool_num_bytes(apr_pool_t *pool, void *data)
{
    apr_size_t *psize = (apr_size_t *)data;
    debug_node_t *node;
    apr_uint32_t index;

    node = pool->nodes;

    while (node) {
        for (index = 0; index < node->index; index++) {
            *psize += (char *)node->endp[index] - (char *)node->beginp[index];
        }

        node = node->next;
    }

    return 0;
}