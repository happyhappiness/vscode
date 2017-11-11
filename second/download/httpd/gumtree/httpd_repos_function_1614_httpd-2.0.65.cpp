static void x_insert_filter(request_rec *r)
{
    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Log the call and exit.
     */
    trace_add(r->server, NULL, cfg, "x_insert_filter()");
}