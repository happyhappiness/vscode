static void notify_suspend(event_conn_state_t *cs)
{
    ap_run_suspend_connection(cs->c, cs->r);
    cs->suspended = 1;
    cs->c->sbh = NULL;
}