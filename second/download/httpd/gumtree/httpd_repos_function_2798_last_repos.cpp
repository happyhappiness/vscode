int h2_beam_report_consumption(h2_bucket_beam *beam)
{
    h2_beam_lock bl;
    int rv = 0;
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        rv = report_consumption(beam, &bl);
        leave_yellow(beam, &bl);
    }
    return rv;
}