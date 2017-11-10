static apr_port_t x_default_port(const request_rec *r)
{
    /*
     * Log the call and exit.
     */
    trace_request(r, "x_default_port()");
    return 0;
}