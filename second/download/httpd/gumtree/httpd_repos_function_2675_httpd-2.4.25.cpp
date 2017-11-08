apr_status_t h2_beam_create(h2_bucket_beam **pbeam, apr_pool_t *pool, 
                            int id, const char *tag, 
                            h2_beam_owner_t owner,
                            apr_size_t max_buf_size)
{
    h2_bucket_beam *beam;
    apr_status_t status = APR_SUCCESS;
    
    beam = apr_pcalloc(pool, sizeof(*beam));
    if (!beam) {
        return APR_ENOMEM;
    }

    beam->id = id;
    beam->tag = tag;
    beam->pool = pool;
    beam->owner = owner;
    H2_BLIST_INIT(&beam->send_list);
    H2_BLIST_INIT(&beam->hold_list);
    H2_BLIST_INIT(&beam->purge_list);
    H2_BPROXY_LIST_INIT(&beam->proxies);
    beam->max_buf_size = max_buf_size;
    apr_pool_pre_cleanup_register(pool, beam, beam_cleanup);

    *pbeam = beam;
    
    return status;
}