static void
dialup_callback(void *baton)
{
    int status;
    dialup_baton_t *db = (dialup_baton_t *)baton;

    apr_thread_mutex_lock(db->r->invoke_mtx);

    status = dialup_send_pulse(db);

    if (status == SUSPENDED) {
        ap_mpm_register_timed_callback(apr_time_from_sec(1), dialup_callback, baton);
    }
    else if (status == DONE) {
        apr_thread_mutex_unlock(db->r->invoke_mtx);
        ap_finalize_request_protocol(db->r);
        ap_process_request_after_handler(db->r);
        return;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, db->r, APLOGNO(01868)
                      "dialup: pulse returned: %d", status);
        db->r->status = HTTP_OK;
        ap_die(status, db->r);
    }

    apr_thread_mutex_unlock(db->r->invoke_mtx);
}