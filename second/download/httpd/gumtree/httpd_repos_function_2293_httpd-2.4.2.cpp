static int x_check_authz(request_rec *r)
{
    /*
     * Log the call and return OK, or access will be denied (even though we
     * didn't actually do anything).
     */
    trace_request(r, "x_check_authz()");
    return DECLINED;
}