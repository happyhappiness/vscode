static int x_post_read_request(request_rec *r)
{
    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_request(r, "x_post_read_request()");
    return DECLINED;
}