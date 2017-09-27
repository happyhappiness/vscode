                                    workers->pool, workers->thread_attr,
                                    get_mplx_next, worker_done, workers);
    if (!w) {
        return APR_ENOMEM;
    }
    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                 "h2_workers: adding worker(%d)", h2_worker_get_id(w));
    ++workers->worker_count;
    H2_WORKER_LIST_INSERT_TAIL(&workers->workers, w);
    return APR_SUCCESS;
}

static apr_status_t h2_workers_start(h2_workers *workers)
