ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02402)
                             "re-grabbing shm[%d] (0x%pp) for worker: %s", i, (void *)shm,
                             ap_proxy_worker_name(conf->pool, worker));