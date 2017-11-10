void ap_pop_pool(apr_pool_t ** recycled_pool, fd_queue_info_t * queue_info)
{
    /* Atomically pop a pool from the recycled list */

    /* This function is safe only as long as it is single threaded because
     * it reaches into the queue and accesses "next" which can change.
     * We are OK today because it is only called from the listener thread.
     * cas-based pushes do not have the same limitation - any number can
     * happen concurrently with a single cas-based pop.
     */

    *recycled_pool = NULL;


    /* Atomically pop a pool from the recycled list */
    for (;;) {
        struct recycled_pool *first_pool = queue_info->recycled_pools;
        if (first_pool == NULL) {
            break;
        }
        if (apr_atomic_casptr
            ((volatile void **) &(queue_info->recycled_pools),
             first_pool->next, first_pool) == first_pool) {
            *recycled_pool = first_pool->pool;
            break;
        }
    }
}