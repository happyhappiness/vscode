int h2_beam_was_received(h2_bucket_beam *beam)
{
    int happend = 0;
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        happend = (beam->received_bytes > 0);
        leave_yellow(beam, &bl);
    }
    return happend;
}