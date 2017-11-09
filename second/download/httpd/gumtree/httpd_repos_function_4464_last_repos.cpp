void ap_free_idle_pools(fd_queue_info_t *queue_info)
{
    apr_pool_t *p;

    queue_info->max_recycled_pools = 0;
    do {
        ap_pop_pool(&p, queue_info);
        if (p != NULL)
            apr_pool_destroy(p);
    } while (p != NULL);
}