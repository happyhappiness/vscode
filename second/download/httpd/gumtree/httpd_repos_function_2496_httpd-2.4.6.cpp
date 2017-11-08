static int x_map_to_storage(request_rec *r)
{
    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_request(r, "x_map_to_storage()");
    return DECLINED;
}