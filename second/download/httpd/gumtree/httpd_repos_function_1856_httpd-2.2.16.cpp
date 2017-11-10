static int x_pre_connection(conn_rec *c, void *csd)
{
    x_cfg *cfg;

    cfg = our_cconfig(c);
#if 0
    /*
     * Log the call and exit.
     */
    trace_add(r->server, NULL, cfg, "x_pre_connection()");
#endif
    return OK;
}