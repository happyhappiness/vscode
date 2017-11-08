static void beam_set_recv_pool(h2_bucket_beam *beam, apr_pool_t *pool) 
{
    /* if the beam owner is the sender, monitor receiver pool lifetime */ 
    if (beam->owner == H2_BEAM_OWNER_SEND && beam->recv_pool != pool) {
        if (beam->recv_pool) {
            apr_pool_cleanup_kill(beam->recv_pool, beam, beam_recv_cleanup);
        }
        beam->recv_pool = pool;
        if (beam->recv_pool) {
            apr_pool_pre_cleanup_register(beam->recv_pool, beam, beam_recv_cleanup);
        }
    }
}