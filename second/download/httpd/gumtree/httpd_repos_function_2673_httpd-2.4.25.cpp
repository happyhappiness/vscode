static apr_status_t beam_cleanup(void *data)
{
    h2_bucket_beam *beam = data;
    apr_status_t status = APR_SUCCESS;
    /* owner of the beam is going away, depending on its role, cleanup
     * strategies differ. */
    beam_close(beam);
    switch (beam->owner) {
        case H2_BEAM_OWNER_SEND:
            status = beam_send_cleanup(beam);
            beam->recv_buffer = NULL;
            beam->recv_pool = NULL;
            break;
        case H2_BEAM_OWNER_RECV:
            if (beam->recv_buffer) {
                apr_brigade_destroy(beam->recv_buffer);
            }
            beam->recv_buffer = NULL;
            beam->recv_pool = NULL;
            if (!H2_BLIST_EMPTY(&beam->send_list)) {
                ap_assert(beam->send_pool);
            }
            if (beam->send_pool) {
                /* sender has not cleaned up, its pool still lives.
                 * this is normal if the sender uses cleanup via a bucket
                 * such as the BUCKET_EOR for requests. In that case, the
                 * beam should have lost its mutex protection, meaning
                 * it is no longer used multi-threaded and we can safely
                 * purge all remaining sender buckets. */
                apr_pool_cleanup_kill(beam->send_pool, beam, beam_send_cleanup);
                ap_assert(!beam->m_enter);
                beam_send_cleanup(beam);
            }
            ap_assert(H2_BPROXY_LIST_EMPTY(&beam->proxies));
            ap_assert(H2_BLIST_EMPTY(&beam->send_list));
            ap_assert(H2_BLIST_EMPTY(&beam->hold_list));
            ap_assert(H2_BLIST_EMPTY(&beam->purge_list));
            break;
        default:
            ap_assert(NULL);
            break;
    }
    return status;
}