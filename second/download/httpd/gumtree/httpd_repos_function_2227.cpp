static int x_monitor(apr_pool_t *p, server_rec *s)
{
    trace_nocontext(p, __FILE__, __LINE__, "x_monitor()");
    return DECLINED;
}