static void pool_clear_debug(apr_pool_t *pool, const char *file_line)
{
    debug_node_t *node;
    apr_uint32_t index;

    /* Destroy the subpools.  The subpools will detach themselves from
     * this pool thus this loop is safe and easy.
     */
    while (pool->child)
        pool_destroy_debug(pool->child, file_line);

    /* Run cleanups */
    run_cleanups(&pool->cleanups);
    pool->free_cleanups = NULL;
    pool->cleanups = NULL;

    /* If new child pools showed up, this is a reason to raise a flag */
    if (pool->child)
        abort();

    /* Free subprocesses */
    free_proc_chain(pool->subprocesses);
    pool->subprocesses = NULL;

    /* Clear the user data. */
    pool->user_data = NULL;

    /* Free the blocks */
    while ((node = pool->nodes) != NULL) {
        pool->nodes = node->next;

        for (index = 0; index < node->index; index++)
            free(node->beginp[index]);

        free(node);
    }

    pool->stat_alloc = 0;
    pool->stat_clear++;
}