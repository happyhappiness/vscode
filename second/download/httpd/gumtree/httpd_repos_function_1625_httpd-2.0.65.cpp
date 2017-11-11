static int x_fixer_upper(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Log the call and exit.
     */
    trace_add(r->server, r, cfg, "x_fixer_upper()");
    return OK;
}