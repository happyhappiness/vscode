static apr_status_t thread_pool_cleanup(void *me)
{
    apr_thread_pool_t *_self = me;

    _self->terminated = 1;
    apr_thread_pool_idle_max_set(_self, 0);
    while (_self->thd_cnt) {
        apr_sleep(20 * 1000);   /* spin lock with 20 ms */
    }
    apr_thread_mutex_destroy(_self->lock);
    apr_thread_cond_destroy(_self->cond);
    return APR_SUCCESS;
}