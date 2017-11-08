static int x_type_checker(request_rec *r)
{
    /*
     * Log the call, but don't do anything else - and report truthfully that
     * we didn't do anything.
     */
    trace_request(r, "x_type_checker()");
    return DECLINED;
}