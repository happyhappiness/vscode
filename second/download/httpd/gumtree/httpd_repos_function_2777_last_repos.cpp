void h2_beam_timeout_set(h2_bucket_beam *beam, apr_interval_time_t timeout)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->timeout = timeout;
        leave_yellow(beam, &bl);
    }
}