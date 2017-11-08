apr_interval_time_t h2_beam_timeout_get(h2_bucket_beam *beam)
{
    h2_beam_lock bl;
    apr_interval_time_t timeout = 0;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        timeout = beam->timeout;
        leave_yellow(beam, &bl);
    }
    return timeout;
}