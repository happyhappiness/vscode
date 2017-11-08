void ap_push_pool(fd_queue_info_t * queue_info,
                                    apr_pool_t * pool_to_recycle)
{
    /* If we have been given a pool to recycle, atomically link
     * it into the queue_info's list of recycled pools
     */
    if (pool_to_recycle) {
        struct recycled_pool *new_recycle;
        new_recycle = (struct recycled_pool *) apr_palloc(pool_to_recycle,
                                                          sizeof
                                                          (*new_recycle));
        new_recycle->pool = pool_to_recycle;
        for (;;) {
            new_recycle->next = queue_info->recycled_pools;
            if (apr_atomic_casptr
                ((volatile void **) &(queue_info->recycled_pools),
                 new_recycle, new_recycle->next) == new_recycle->next) {
                break;
            }
        }
    }
}