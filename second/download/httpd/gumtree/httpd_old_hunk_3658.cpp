                 "socket reached timeout in lingering-close state");
    rv = apr_socket_close(csd);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00468) "error closing socket");
        AP_DEBUG_ASSERT(0);
    }
    apr_pool_clear(cs->p);
    ap_push_pool(worker_queue_info, cs->p);
    return 0;
}

static void notify_suspend(event_conn_state_t *cs)
{
    ap_run_suspend_connection(cs->c, cs->r);
    cs->suspended = 1;
}

static void notify_resume(event_conn_state_t *cs)
{
    cs->suspended = 0;
    ap_run_resume_connection(cs->c, cs->r);
}

/*
 * This runs before any non-MPM cleanup code on the connection;
 * if the connection is currently suspended as far as modules
 * know, provide notification of resumption.
 */
static apr_status_t ptrans_pre_cleanup(void *dummy)
