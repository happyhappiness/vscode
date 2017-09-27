         * socket to a worker
         */
        apr_bucket_alloc_destroy(cs->bucket_alloc);
        apr_socket_close(cs->pfd.desc.s);
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                     ap_server_conf, APLOGNO(00471) "push2worker: ap_queue_push failed");
        ap_push_pool(worker_queue_info, cs->p);
    }

    return rc;
}

