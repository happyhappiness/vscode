static apr_status_t beam_send_cleanup(void *data)
{
    h2_bucket_beam *beam = data;
    /* sender has gone away, clear up all references to its memory */
    r_purge_sent(beam);
    h2_blist_cleanup(&beam->send_list);
    report_consumption(beam, 0);
    while (!H2_BPROXY_LIST_EMPTY(&beam->proxies)) {
        h2_beam_proxy *proxy = H2_BPROXY_LIST_FIRST(&beam->proxies);
        H2_BPROXY_REMOVE(proxy);
        proxy->beam = NULL;
        proxy->bred = NULL;
    }
    h2_blist_cleanup(&beam->purge_list);
    h2_blist_cleanup(&beam->hold_list);
    beam->send_pool = NULL;
    return APR_SUCCESS;
}