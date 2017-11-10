static int x_header_parser(request_rec *r)
{
    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_request(r, "x_header_parser()");
    return DECLINED;
}