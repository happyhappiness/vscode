        if (ep->when > te->when) {
            inserted = 1;
            APR_RING_INSERT_BEFORE(ep, te, link);
            break;
        }
    }
    
    if (!inserted) {
        APR_RING_INSERT_TAIL(&timer_ring, te, timer_event_t, link);
    }

    apr_thread_mutex_unlock(g_timer_ring_mtx);

    return APR_SUCCESS;
}

static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
{
    timer_event_t *ep;
    timer_event_t *te;
    apr_status_t rc;
    proc_info *ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans;         /* Pool for per-transaction stuff */
    ap_listen_rec *lr;
    int have_idle_worker = 0;
    conn_state_t *cs;
    const apr_pollfd_t *out_pfd;
    apr_int32_t num = 0;
    apr_time_t time_now = 0;
    apr_interval_time_t timeout_interval;
    apr_time_t timeout_time;
    listener_poll_type *pt;

    free(ti);

    /* the following times out events that are really close in the future
     *   to prevent extra poll calls
     *
     * current value is .1 second
