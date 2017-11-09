static apr_status_t beam_cleanup(void *data)
{
    h2_bucket_beam *beam = data;
    apr_status_t status = APR_SUCCESS;
    int safe_send = !beam->m_enter || (beam->owner == H2_BEAM_OWNER_SEND);
    int safe_recv = !beam->m_enter || (beam->owner == H2_BEAM_OWNER_RECV);
    
    /* 
     * Owner of the beam is going away, depending on which side it owns,
     * cleanup strategies will differ with multi-thread protection
     * still in place (beam->m_enter).
     *
     * In general, receiver holds references to memory from sender. 
     * Clean up receiver first, if safe, then cleanup sender, if safe.
     */
     
    /* When modify send is not safe, this means we still have multi-thread
     * protection and the owner is receiving the buckets. If the sending
     * side has not gone away, this means we could have dangling buckets
     * in our lists that never get destroyed. This should not happen. */
    ap_assert(safe_send || !beam->send_pool);
    if (!H2_BLIST_EMPTY(&beam->send_list)) {
        ap_assert(beam->send_pool);
    }
    
    if (safe_recv) {
        if (beam->recv_pool) {
            pool_kill(beam, beam->recv_pool, beam_recv_cleanup);
            beam->recv_pool = NULL;
        }
        recv_buffer_cleanup(beam, NULL);
    }
    else {
        beam->recv_buffer = NULL;
        beam->recv_pool = NULL;
    }
    
    if (safe_send && beam->send_pool) {
        pool_kill(beam, beam->send_pool, beam_send_cleanup);
        status = beam_send_cleanup(beam);
    }
    
    if (safe_recv) {
        ap_assert(H2_BPROXY_LIST_EMPTY(&beam->proxies));
        ap_assert(H2_BLIST_EMPTY(&beam->send_list));
        ap_assert(H2_BLIST_EMPTY(&beam->hold_list));
        ap_assert(H2_BLIST_EMPTY(&beam->purge_list));
    }
    return status;
}