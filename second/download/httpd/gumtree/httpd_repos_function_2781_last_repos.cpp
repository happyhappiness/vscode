apr_status_t h2_beam_leave(h2_bucket_beam *beam)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        recv_buffer_cleanup(beam, &bl);
        beam->aborted = 1;
        beam_close(beam);
        leave_yellow(beam, &bl);
    }
    return APR_SUCCESS;
}