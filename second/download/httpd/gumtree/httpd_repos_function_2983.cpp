static void *simple_timer_invoke(apr_thread_t * thread, void *baton)
{
    simple_timer_t *ep = (simple_timer_t *) baton;

    simple_timer_run(ep);

    return NULL;
}