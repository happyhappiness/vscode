static int start_lingering_close_blocking(event_conn_state_t *cs)
{
    if (ap_start_lingering_close(cs->c)) {
        notify_suspend(cs);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return start_lingering_close_common(cs, 1);
}