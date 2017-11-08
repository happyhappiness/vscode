static apr_status_t queue_info_cleanup(void *data_)
{
    fd_queue_info_t *qi = data_;
    int i;
    apr_thread_cond_destroy(qi->wait_for_idler);
    apr_thread_mutex_destroy(qi->idlers_mutex);
    for (i = 0; i < qi->num_recycled; i++) {
        apr_pool_destroy(qi->recycled_pools[i]);
    }
    return APR_SUCCESS;
}