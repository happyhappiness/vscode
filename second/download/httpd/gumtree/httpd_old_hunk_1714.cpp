        worker->is_address_reusable = 0;
    }
    else {
        worker->is_address_reusable = 1;
    }

#if APR_HAS_THREADS
    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
    if (mpm_threads > 1) {
        /* Set hard max to no more then mpm_threads */
        if (worker->hmax == 0 || worker->hmax > mpm_threads) {
            worker->hmax = mpm_threads;
        }
