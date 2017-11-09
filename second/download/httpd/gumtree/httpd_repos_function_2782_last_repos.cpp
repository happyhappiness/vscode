apr_status_t h2_beam_wait_empty(h2_bucket_beam *beam, apr_read_type_e block)
{
    apr_status_t status;
    h2_beam_lock bl;
    
    if ((status = enter_yellow(beam, &bl)) == APR_SUCCESS) {
        while (status == APR_SUCCESS
               && !H2_BLIST_EMPTY(&beam->send_list)
               && !H2_BPROXY_LIST_EMPTY(&beam->proxies)) {
            if (block == APR_NONBLOCK_READ || !bl.mutex) {
                status = APR_EAGAIN;
                break;
            }
            if (beam->cond) {
                apr_thread_cond_broadcast(beam->cond);
            }
            status = wait_cond(beam, bl.mutex);
        }
        leave_yellow(beam, &bl);
    }
    return status;
}