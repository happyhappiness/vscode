static apr_status_t beam_close(h2_bucket_beam *beam)
{
    if (!beam->closed) {
        beam->closed = 1;
        if (beam->cond) {
            apr_thread_cond_broadcast(beam->cond);
        }
    }
    return APR_SUCCESS;
}