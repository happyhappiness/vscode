static apr_status_t thread_pool_cleanup(void *me)
{
    apr_thread_pool_t *_myself = me;

    _myself->terminated = 1;
    apr_thread_pool_idle_max_set(_myself, 0);
    while (_myself->thd_cnt) {
        apr_sleep(20 * 1000);   /* spin lock with 20 ms */
    }
    apr_thread_mutex_destroy(_myself->lock);
    apr_thread_cond_destroy(_myself->cond);
    return APR_SUCCESS;
}