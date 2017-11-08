static int x_access_checker(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    trace_add(r->server, r, cfg, "x_access_checker()");
    return DECLINED;
}