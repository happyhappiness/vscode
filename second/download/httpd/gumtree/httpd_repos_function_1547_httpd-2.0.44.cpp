static int x_quick_handler(request_rec *r, int lookup_uri)
{
    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Log the call and exit.
     */
    trace_add(r->server, NULL, cfg, "x_post_config()");
    return DECLINED;
}