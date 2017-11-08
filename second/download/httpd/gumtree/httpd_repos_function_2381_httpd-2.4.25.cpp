void h2_mplx_task_done(h2_mplx *m, h2_task *task, h2_task **ptask)
{
    int acquired;
    
    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
        task_done(m, task, NULL);
        --m->workers_busy;
        if (m->join_wait) {
            apr_thread_cond_signal(m->join_wait);
        }
        if (ptask) {
            /* caller wants another task */
            *ptask = next_stream_task(m);
        }
        leave_mutex(m, acquired);
    }
}