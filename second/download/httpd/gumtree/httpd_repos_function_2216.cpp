static int x_check_access(request_rec *r)
{
    trace_request(r, "x_check_access()");
    return DECLINED;
}