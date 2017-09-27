        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                     "start_lingering_close: apr_pollset_add failure");
        apr_thread_mutex_lock(timeout_mutex);
        TO_QUEUE_REMOVE(*q, cs);
        apr_thread_mutex_unlock(timeout_mutex);
        apr_socket_close(cs->pfd.desc.s);
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return 1;
}

