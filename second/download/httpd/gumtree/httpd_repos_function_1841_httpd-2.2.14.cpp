static int x_logger(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    trace_add(r->server, r, cfg, "x_logger()");
    return DECLINED;
}