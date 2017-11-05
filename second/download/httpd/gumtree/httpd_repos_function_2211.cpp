static int x_process_connection(conn_rec *c)
{
    x_cfg *cfg;
    cfg = our_cconfig(c);
    
    trace_connection(c, "x_process_connection()");
    
    return DECLINED;
}