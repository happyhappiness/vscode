static APR_INLINE
apr_memnode_t *allocator_alloc(apr_allocator_t *allocator, apr_size_t in_size)
{
    apr_memnode_t *node, **ref;
    apr_uint32_t i, index, max_index;
    apr_size_t size;

    /* Round up the block size to the next boundary, but always
     * allocate at least a certain size (MIN_ALLOC).
     */
    size = APR_ALIGN(in_size + APR_MEMNODE_T_SIZE, BOUNDARY_SIZE);
    if (size < in_size) {
        return NULL;
    }
    if (size < MIN_ALLOC)
        size = MIN_ALLOC;

    /* Find the index for this node size by
     * dividing its size by the boundary size
     */
    index = (size >> BOUNDARY_INDEX) - 1;

    /* First see if there are any nodes in the area we know
     * our node will fit into.
     */
    if (index <= allocator->max_index) {
#if APR_HAS_THREADS
        if (allocator->mutex)
            apr_thread_mutex_lock(allocator->mutex);
#endif /* APR_HAS_THREADS */

        /* Walk the free list to see if there are
         * any nodes on it of the requested size
         *
         * NOTE: an optimization would be to check
         * allocator->free[index] first and if no
         * node is present, directly use
         * allocator->free[max_index].  This seems
         * like overkill though and could cause
         * memory waste.
         */
        max_index = allocator->max_index;
        ref = &allocator->free[index];
        i = index;
        while (*ref == NULL && i < max_index) {
           ref++;
           i++;
        }

        if ((node = *ref) != NULL) {
            /* If we have found a node and it doesn't have any
             * nodes waiting in line behind it _and_ we are on
             * the highest available index, find the new highest
             * available index
             */
            if ((*ref = node->next) == NULL && i >= max_index) {
                do {
                    ref--;
                    max_index--;
                }
                while (*ref == NULL && max_index > 0);

                allocator->max_index = max_index;
            }

            allocator->current_free_index += node->index;
            if (allocator->current_free_index > allocator->max_free_index)
                allocator->current_free_index = allocator->max_free_index;

#if APR_HAS_THREADS
            if (allocator->mutex)
                apr_thread_mutex_unlock(allocator->mutex);
#endif /* APR_HAS_THREADS */

            node->next = NULL;
            node->first_avail = (char *)node + APR_MEMNODE_T_SIZE;

            return node;
        }

#if APR_HAS_THREADS
        if (allocator->mutex)
            apr_thread_mutex_unlock(allocator->mutex);
#endif /* APR_HAS_THREADS */
    }

    /* If we found nothing, seek the sink (at index 0), if
     * it is not empty.
     */
    else if (allocator->free[0]) {
#if APR_HAS_THREADS
        if (allocator->mutex)
            apr_thread_mutex_lock(allocator->mutex);
#endif /* APR_HAS_THREADS */

        /* Walk the free list to see if there are
         * any nodes on it of the requested size
         */
        ref = &allocator->free[0];
        while ((node = *ref) != NULL && index > node->index)
            ref = &node->next;

        if (node) {
            *ref = node->next;

            allocator->current_free_index += node->index;
            if (allocator->current_free_index > allocator->max_free_index)
                allocator->current_free_index = allocator->max_free_index;

#if APR_HAS_THREADS
            if (allocator->mutex)
                apr_thread_mutex_unlock(allocator->mutex);
#endif /* APR_HAS_THREADS */

            node->next = NULL;
            node->first_avail = (char *)node + APR_MEMNODE_T_SIZE;

            return node;
        }

#if APR_HAS_THREADS
        if (allocator->mutex)
            apr_thread_mutex_unlock(allocator->mutex);
#endif /* APR_HAS_THREADS */
    }

    /* If we haven't got a suitable node, malloc a new one
     * and initialize it.
     */
    if ((node = malloc(size)) == NULL)
        return NULL;

    node->next = NULL;
    node->index = index;
    node->first_avail = (char *)node + APR_M