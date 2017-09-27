        found = 0;
        workers = (proxy_worker **)b->workers->elts;
        for (i = 0; i < b->workers->nelts; i++, workers++) {
            proxy_worker *worker = *workers;
            if (worker->hash.def == shm->hash.def && worker->hash.fnv == shm->hash.fnv) {
                found = 1;
                break;
            }
        }
        if (!found) {
            proxy_worker **runtime;
            runtime = apr_array_push(b->workers);
