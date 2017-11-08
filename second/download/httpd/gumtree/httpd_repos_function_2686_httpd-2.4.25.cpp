apr_status_t h2_beam_send(h2_bucket_beam *beam, 
                          apr_bucket_brigade *red_brigade, 
                          apr_read_type_e block)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    h2_beam_lock bl;

    /* Called from the red thread to add buckets to the beam */
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        r_purge_sent(beam);
        if (red_brigade) {
            beam_set_send_pool(beam, red_brigade->p);
        }
        
        if (beam->aborted) {
            move_to_hold(beam, red_brigade);
            status = APR_ECONNABORTED;
        }
        else if (red_brigade) {
            int force_report = !APR_BRIGADE_EMPTY(red_brigade); 
            while (!APR_BRIGADE_EMPTY(red_brigade)
                   && status == APR_SUCCESS) {
                b = APR_BRIGADE_FIRST(red_brigade);
                status = append_bucket(beam, b, block, &bl);
            }
            report_production(beam, force_report);
            if (beam->m_cond) {
                apr_thread_cond_broadcast(beam->m_cond);
            }
        }
        report_consumption(beam, 0);
        leave_yellow(beam, &bl);
    }
    return status;
}