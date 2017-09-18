            else if (!workers_may_exit) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "ap_queue_pop failed");
            }
            continue;
        }
        worker_sockets[thread_slot] = csd;
        process_socket(ptrans, csd, process_slot, thread_slot, bucket_alloc);
        worker_sockets[thread_slot] = NULL;
        requests_this_child--; /* FIXME: should be synchronized - aaron */
        apr_pool_clear(ptrans);
        last_ptrans = ptrans;
