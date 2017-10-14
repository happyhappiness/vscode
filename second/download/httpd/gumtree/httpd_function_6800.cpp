apr_status_t h2_mplx_idle(h2_mplx *m)
{
    apr_status_t status = APR_SUCCESS;
    apr_time_t now;            
    int acquired;
    
    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
        apr_size_t scount = h2_ihash_count(m->streams);
        if (scount > 0 && m->workers_busy) {
            /* If we have streams in connection state 'IDLE', meaning
             * all streams are ready to sent data out, but lack
             * WINDOW_UPDATEs. 
             * 
             * This is ok, unless we have streams that still occupy
             * h2 workers. As worker threads are a scarce resource, 
             * we need to take measures that we do not get DoSed.
             * 
             * This is what we call an 'idle block'. Limit the amount 
             * of busy workers we allow for this connection until it
             * well behaves.
             */
            now = apr_time_now();
            m->last_idle_block = now;
            if (m->workers_limit > 2 
                && now - m->last_limit_change >= m->limit_change_interval) {
                if (m->workers_limit > 16) {
                    m->workers_limit = 16;
                }
                else if (m->workers_limit > 8) {
                    m->workers_limit = 8;
                }
                else if (m->workers_limit > 4) {
                    m->workers_limit = 4;
                }
                else if (m->workers_limit > 2) {
                    m->workers_limit = 2;
                }
                m->last_limit_change = now;
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                              "h2_mplx(%ld): decrease worker limit to %d",
                              m->id, m->workers_limit);
            }
            
            if (m->workers_busy > m->workers_limit) {
                status = unschedule_slow_tasks(m);
            }
        }
        leave_mutex(m, acquired);
    }
    return status;
}