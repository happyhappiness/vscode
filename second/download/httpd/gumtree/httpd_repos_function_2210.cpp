static int x_pre_connection(conn_rec *c, void *csd)
{
    x_cfg *cfg;
    char *note; 

    cfg = our_cconfig(c);

    /*
     * Log the call and exit.
     */
    note = apr_psprintf(c->pool, "x_pre_connection(c = %pp, p = %pp)", 
                        (void*) c, (void*) c->pool);
    trace_connection(c, note);

    return OK;
}