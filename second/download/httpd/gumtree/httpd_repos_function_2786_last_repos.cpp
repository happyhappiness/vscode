apr_status_t h2_beam_send(h2_bucket_beam *beam, 
                          apr_bucket_brigade *sender_bb, 
                          apr_read_type_e block)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    h2_beam_lock bl;

    /* Called from the sender thread to add buckets to the beam */
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        ap_assert(beam->send_pool);
        r_purge_sent(beam);
        
        if (beam->aborted) {
            move_to_hold(beam, sender_bb);
            status = APR_ECONNABORTED;
        }
        else if (sender_bb) {
            int force_report = !APR_BRIGADE_EMPTY(sender_bb); 
            while (!APR_BRIGADE_EMPTY(sender_bb) && status == APR_SUCCESS) {
                b = APR_BRIGADE_FIRST(sender_bb);
                status = append_bucket(beam, b, block, &bl);
            }
            report_prod_io(beam, force_report, &bl);
            if (beam->cond) {
                apr_thread_cond_broadcast(beam->cond);
            }
        }
        report_consumption(beam, &bl);
        leave_yellow(beam, &bl);
    }
    return status;
}