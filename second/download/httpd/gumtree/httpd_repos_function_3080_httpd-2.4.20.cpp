static const char *x_http_scheme(const request_rec *r)
{
    /*
     * Log the call and exit.
     */
    trace_request(r, "x_http_scheme()");

    /* We have no claims to make about the request scheme */
    return NULL;
}