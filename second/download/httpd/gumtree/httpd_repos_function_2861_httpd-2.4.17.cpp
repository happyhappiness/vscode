static int x_fixups(request_rec *r)
{
    /*
     * Log the call and exit.
     */
    trace_request(r, "x_fixups()");
    return DECLINED;
}