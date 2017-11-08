static apr_status_t unschedule_slow_tasks(h2_mplx *m) 
{
    h2_task *task;
    int n;
    
    /* Try to get rid of streams that occupy workers. Look for safe requests
     * that are repeatable. If none found, fail the connection.
     */
    n = (m->workers_busy - m->workers_limit - (int)h2_ihash_count(m->redo_tasks));
    while (n > 0 && (task = get_latest_repeatable_unsubmitted_task(m))) {
        h2_task_rst(task, H2_ERR_CANCEL);
        h2_ihash_add(m->redo_tasks, task);
        --n;
    }
    
    if ((m->workers_busy - h2_ihash_count(m->redo_tasks)) > m->workers_limit) {
        task = get_timed_out_busy_task(m);
        if (task) {
            /* Too many busy workers, unable to cancel enough streams
             * and with a busy, timed out stream, we tell the client
             * to go away... */
            return APR_TIMEUP;
        }
    }
    return APR_SUCCESS;
}