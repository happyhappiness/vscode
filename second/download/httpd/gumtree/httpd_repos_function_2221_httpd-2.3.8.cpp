static int x_log_transaction(request_rec *r)
{
    trace_request(r, "x_log_transaction()");
    return DECLINED;
}