static void beam_set_send_pool(h2_bucket_beam *beam, apr_pool_t *pool) 
{
    /* if the beam owner is the receiver, monitor sender pool lifetime */
    if (beam->owner == H2_BEAM_OWNER_RECV && beam->send_pool != pool) {
        if (beam->send_pool) {
            apr_pool_cleanup_kill(beam->send_pool, beam, beam_send_cleanup);
        }
        beam->send_pool = pool;
        if (beam->send_pool) {
            apr_pool_pre_cleanup_register(beam->send_pool, beam, beam_send_cleanup);
        }
    }
}