static APR_INLINE
void allocator_free(apr_allocator_t *allocator, apr_memnode_t *node)
{
    apr_memnode_t *next, *freelist = NULL;
    apr_uint32_t index, max_index;
    apr_uint32_t max_free_index, current_free_index;

#if APR_HAS_THREADS
    if (allocator->mutex)
        apr_thread_mutex_lock(allocator->mutex);
#endif /* APR_HAS_THREADS */

    max_index = allocator->max_index;
    max_free_index = allocator->max_free_index;
    current_free_index = allocator->current_free_index;

    /* Walk the list of submitted nodes and free them one by one,
     * shoving them in the right 'size' buckets as we go.
     */
    do {
        next = node->next;
        index = node->index;

        if (max_free_index != APR_ALLOCATOR_MAX_FREE_UNLIMITED
            && index > current_free_index) {
            node->next = freelist;
            freelist = node;
        }
        else if (index < MAX_INDEX) {
            /* Add the node to the appropiate 'size' bucket.  Adjust
             * the max_index when appropiate.
             */
            if ((node->next = allocator->free[index]) == NULL
                && index > max_index) {
                max_index = index;
            }
            allocator->free[index] = node;
            if (current_free_index >= index)
                current_free_index -= index;
            else
                current_free_index = 0;
        }
        else {
            /* This node is too large to keep in a specific size bucket,
             * just add it to the sink (at index 0).
             */
            node->next = allocator->free[0];
            allocator->free[0] = node;
            if (current_free_index >= index)
                current_free_index -= index;
            else
                current_free_index = 0;
        }
    } while ((node = next) != NULL);

    allocator->max_index = max_index;
    allocator->current_free_index = current_free_index;

#if APR_HAS_THREADS
    if (allocator->mutex)
        apr_thread_mutex_unlock(allocator->mutex);
#endif /* APR_HAS_THREADS */

    while (freelist != NULL) {
        node = freelist;
        freelist = node->next;
        free(node);
    }
}