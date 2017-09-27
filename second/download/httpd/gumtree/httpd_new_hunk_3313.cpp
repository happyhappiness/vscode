        apr_socket_opt_set(pfd->desc.s, APR_SO_NONBLOCK, 1);
        apr_pollset_add(event_pollset, pfd);

        lr->accept_func = ap_unixd_accept;
    }

    return APR_SUCCESS;
}

static apr_status_t push_timer2worker(timer_event_t* te)
{
    return ap_queue_push_timer(worker_queue, te);
}

/*
 * Pre-condition: pfd->cs is neither in pollset nor timeout queue
 * this function may only be called by the listener
 */
static apr_status_t push2worker(const apr_pollfd_t * pfd,
                                apr_pollset_t * pollset)
{
    listener_poll_type *pt = (listener_poll_type *) pfd->client_data;
    event_conn_state_t *cs = (event_conn_state_t *) pt->baton;
    apr_status_t rc;

    rc = ap_queue_push(worker_queue, cs->pfd.desc.s, cs, cs->p);
    if (rc != APR_SUCCESS) {
        /* trash the connection; we couldn't queue the connected
         * socket to a worker
         */
        apr_bucket_alloc_destroy(cs->bucket_alloc);
        apr_socket_close(cs->pfd.desc.s);
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                     ap_server_conf, APLOGNO(00471) "push2worker: ap_queue_push failed");
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
    }

    return rc;
}

/* get_worker:
 *     If *have_idle_worker_p == 0, reserve a worker thread, and set
 *     *have_idle_worker_p = 1.
 *     If *have_idle_worker_p is already 1, will do nothing.
 *     If blocking == 1, block if all workers are currently busy.
 *     If no worker was available immediately, will set *all_busy to 1.
 *     XXX: If there are no workers, we should not block immediately but
 *     XXX: close all keep-alive connections first.
 */
static void get_worker(int *have_idle_worker_p, int blocking, int *all_busy)
{
    apr_status_t rc;

    if (*have_idle_worker_p) {
        /* already reserved a worker thread - must have hit a
         * transient error on a previous pass
         */
        return;
    }

    if (blocking)
        rc = ap_queue_info_wait_for_idler(worker_queue_info, all_busy);
    else
        rc = ap_queue_info_try_get_idler(worker_queue_info);

    if (rc == APR_SUCCESS) {
        *have_idle_worker_p = 1;
    }
    else if (!blocking && rc == APR_EAGAIN) {
        *all_busy = 1;
    }
    else if (!APR_STATUS_IS_EOF(rc)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf, APLOGNO(00472)
                     "ap_queue_info_wait_for_idler failed.  "
                     "Attempting to shutdown process gracefully");
        signal_threads(ST_GRACEFUL);
    }
}

/* XXXXXX: Convert to skiplist or other better data structure
 * (yes, this is VERY VERY VERY VERY BAD)
 */

/* Structures to reuse */
static APR_RING_HEAD(timer_free_ring_t, timer_event_t) timer_free_ring;
/* Active timers */
