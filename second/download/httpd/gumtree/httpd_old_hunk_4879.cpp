            /* now go thru each worker */
            workers = (proxy_worker **)balancer->workers->elts;
            for (j = 0; j < balancer->workers->nelts; j++, workers++) {
                proxy_worker_shared *shm;

                worker = *workers;
                if ((rv = storage->grab(balancer->wslot, &index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01186) "worker slotmem_grab failed");
                    return !OK;

                }
                if ((rv = storage->dptr(balancer->wslot, index, (void *)&shm)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01187) "worker slotmem_dptr failed");
                    return !OK;
                }
                if ((rv = ap_proxy_share_worker(worker, shm, index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01188) "Cannot share worker");
                    return !OK;
                }
                worker->s->updated = tstamp;
            }
        }
        s = s->next;
    }

    return OK;
}
