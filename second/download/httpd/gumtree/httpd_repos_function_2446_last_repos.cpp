apr_status_t h2_mplx_out_trywait(h2_mplx *m, apr_interval_time_t timeout,
                                 apr_thread_cond_t *iowait)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else if (h2_mplx_has_master_events(m)) {
        status = APR_SUCCESS;
    }
    else {
        purge_streams(m, 0);
        h2_ihash_iter(m->streams, report_consumption_iter, m);
        m->added_output = iowait;
        status = apr_thread_cond_timedwait(m->added_output, m->lock, timeout);
        if (APLOGctrace2(m->c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): trywait on data for %f ms)",
                          m->id, timeout/1000.0);
        }
        m->added_output = NULL;
    }

    H2_MPLX_LEAVE(m);
    return status;
}