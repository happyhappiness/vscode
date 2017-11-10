static int x_auth_checker(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Log the call and return OK, or access will be denied (even though we
     * didn't actually do anything).
     */
    trace_add(r->server, r, cfg, "x_auth_checker()");
    return DECLINED;
}