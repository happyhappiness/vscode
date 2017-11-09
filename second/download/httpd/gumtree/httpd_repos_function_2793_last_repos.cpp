int h2_beam_empty(h2_bucket_beam *beam)
{
    int empty = 1;
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        empty = (H2_BLIST_EMPTY(&beam->send_list) 
                 && (!beam->recv_buffer || APR_BRIGADE_EMPTY(beam->recv_buffer)));
        leave_yellow(beam, &bl);
    }
    return empty;
}