void h2_beam_buffer_size_set(h2_bucket_beam *beam, apr_size_t buffer_size)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->max_buf_size = buffer_size;
        leave_yellow(beam, &bl);
    }
}