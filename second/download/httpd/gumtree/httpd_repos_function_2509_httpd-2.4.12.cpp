static int x_quick_handler(request_rec *r, int lookup_uri)
{
    /*
     * Log the call and exit.
     */
    trace_request(r, "x_quick_handler()");
    return DECLINED;
}