static int x_check_authn(request_rec *r)
{
    /*
     * Don't do anything except log the call.
     */
    trace_request(r, "x_check_authn()");
    return DECLINED;
}