static int x_create_request(request_rec *r)
{
    /*
     * We have a request_rec, but it is not filled in enough to give
     * us a usable configuration. So, add a trace without context.
     */
    trace_nocontext( r->pool, __FILE__, __LINE__, "x_create_request()");
    return DECLINED;
}