static int x_check_user_id(request_rec *r)
{

    x_cfg *cfg;

    cfg = our_dconfig(r);
    /*
     * Don't do anything except log the call.
     */
    trace_add(r->server, r, cfg, "x_check_user_id()");
    return DECLINED;
}