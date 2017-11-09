void h2_beam_send_from(h2_bucket_beam *beam, apr_pool_t *p)
{
    h2_beam_lock bl;
    /* Called from the sender thread to add buckets to the beam */
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        r_purge_sent(beam);
        beam_set_send_pool(beam, p);
        leave_yellow(beam, &bl);
    }
}