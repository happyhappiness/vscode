static void notify_resume(event_conn_state_t *cs)
{
    cs->suspended = 0;
    ap_run_resume_connection(cs->c, cs->r);
}