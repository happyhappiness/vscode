                             worker->s->name);
                break;
            }
        }
        if (!found) {
            proxy_worker **runtime;
            runtime = apr_array_push(b->workers);
            *runtime = apr_palloc(conf->pool, sizeof(proxy_worker));
            (*runtime)->hash = shm->hash;
            (*runtime)->context = NULL;
            (*runtime)->cp = NULL;
            (*runtime)->balancer = b;
            (*runtime)->s = shm;
            (*runtime)->tmutex = NULL;
            if ((rv = ap_proxy_initialize_worker(*runtime, s, conf->pool)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00966) "Cannot init worker");
                return rv;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02403)
                         "grabbing shm[%d] (0x%pp) for worker: %s", i, (void *)shm,
                         (*runtime)->s->name);
