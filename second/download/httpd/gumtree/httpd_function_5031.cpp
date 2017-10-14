static int stop_lingering_close(event_conn_state_t *cs)
{
    apr_status_t rv;
    apr_socket_t *csd = ap_get_conn_socket(cs->c);
    ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
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