static apr_status_t check_pipe_of_death(void **csd, ap_listen_rec *lr,
                                        apr_pool_t *ptrans)
{
    apr_thread_mutex_lock(pipe_of_death_mutex);
    if (!workers_may_exit) {
        int ret;
        char pipe_read_char;
        apr_size_t n = 1;

        ret = apr_recv(lr->sd, &pipe_read_char, &n);
        if (APR_STATUS_IS_EAGAIN(ret)) {
            /* It lost the lottery. It must continue to suffer
             * through a life of servitude. */
        }
        else {
            /* It won the lottery (or something else is very
             * wrong). Embrace death with open arms. */
            workers_may_exit = 1;
        }
    }
    apr_thread_mutex_unlock(pipe_of_death_mutex);
    return APR_SUCCESS;
}