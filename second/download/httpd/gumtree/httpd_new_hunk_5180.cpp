        for (i = 0; i < b->workers->nelts; i++, workers++) {
            proxy_worker *worker = *workers;
            if (worker->hash.def == shm->hash.def && worker->hash.fnv == shm->hash.fnv) {
                found = 1;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02402)
                             "re-grabbing shm[%d] (0x%pp) for worker: %s", i, (void *)shm,
                             ap_proxy_worker_name(conf->pool, worker));
                break;
            }
        }
        if (!found) {
            proxy_worker **runtime;
            apr_global_mutex_lock(proxy_mutex);
