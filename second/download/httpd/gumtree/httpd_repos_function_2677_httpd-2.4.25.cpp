apr_size_t h2_beam_buffer_size_get(h2_bucket_beam *beam)
{
    h2_beam_lock bl;
    apr_size_t buffer_size = 0;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        buffer_size = beam->max_buf_size;
        leave_yellow(beam, &bl);
    }
    return buffer_size;
}