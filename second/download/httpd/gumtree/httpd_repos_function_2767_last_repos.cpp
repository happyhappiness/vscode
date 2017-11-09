static void beam_set_send_pool(h2_bucket_beam *beam, apr_pool_t *pool) 
{
    if (beam->send_pool != pool) {
        if (beam->send_pool && beam->send_pool != beam->pool) {
            pool_kill(beam, beam->send_pool, beam_send_cleanup);
            beam_send_cleanup(beam);
        }
        beam->send_pool = pool;
        pool_register(beam, beam->send_pool, beam_send_cleanup);
    }
}