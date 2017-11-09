apr_status_t h2_beam_close(h2_bucket_beam *beam)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        r_purge_sent(beam);
        beam_close(beam);
        report_consumption(beam, &bl);
        leave_yellow(beam, &bl);
    }
    return beam->aborted? APR_ECONNABORTED : APR_SUCCESS;
}