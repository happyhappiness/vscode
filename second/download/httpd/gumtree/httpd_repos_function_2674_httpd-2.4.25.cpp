apr_status_t h2_beam_destroy(h2_bucket_beam *beam)
{
    apr_pool_cleanup_kill(beam->pool, beam, beam_cleanup);
    return beam_cleanup(beam);
}