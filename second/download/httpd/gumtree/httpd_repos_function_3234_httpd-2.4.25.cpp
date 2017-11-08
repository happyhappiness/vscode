static void x_pre_read_request(request_rec *r, conn_rec *c)
{
    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_request(r, "x_pre_read_request()");
}