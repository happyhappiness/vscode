void
simple_timer_run(simple_timer_t *ep)
{
    apr_pool_cleanup_kill(ep->pool, ep, simple_timer_pool_cleanup);

    ep->cb(ep->sc, ep->baton);
}