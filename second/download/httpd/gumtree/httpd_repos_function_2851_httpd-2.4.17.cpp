static int x_process_connection(conn_rec *c)
{
    trace_connection(c, "x_process_connection()");
    return DECLINED;
}