        }
        
        /* Here, we either have gotten task and mplx for the worker or
         * needed to give up with more than enough workers.
         */
        if (task) {
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                         "h2_worker(%d): start task(%s)",
                         h2_worker_get_id(worker), task->id);
            /* Since we hand out a reference to the worker, we increase
             * its ref count.
             */
            h2_mplx_reference(m);
