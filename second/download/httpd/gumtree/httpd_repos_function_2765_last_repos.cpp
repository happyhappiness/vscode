static apr_status_t beam_recv_cleanup(void *data)
{
    h2_bucket_beam *beam = data;
    /* receiver pool has gone away, clear references */
    beam->recv_buffer = NULL;
    beam->recv_pool = NULL;
    return APR_SUCCESS;
}