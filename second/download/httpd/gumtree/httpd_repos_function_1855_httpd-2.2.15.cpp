static int x_post_read_request(request_rec *r)
{
    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_add(r->server, r, cfg, "x_post_read_request()");
    return DECLINED;
}