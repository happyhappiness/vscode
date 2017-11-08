static int x_translate_name(request_rec *r)
{

    /*
     * We don't actually *do* anything here, except note the fact that we were
     * called.
     */
    trace_request(r, "x_translate_name()");
    return DECLINED;
}