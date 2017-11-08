static int x_type_checker(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Log the call, but don't do anything else - and report truthfully that
     * we didn't do anything.
     */
    trace_add(r->server, r, cfg, "x_type_checker()");
    return DECLINED;
}