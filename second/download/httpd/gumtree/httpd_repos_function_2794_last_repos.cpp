int h2_beam_holds_proxies(h2_bucket_beam *beam)
{
    int has_proxies = 1;
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        has_proxies = !H2_BPROXY_LIST_EMPTY(&beam->proxies);
        leave_yellow(beam, &bl);
    }
    return has_proxies;
}