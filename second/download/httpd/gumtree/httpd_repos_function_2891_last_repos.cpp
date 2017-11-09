h2_ngn_shed *h2_ngn_shed_create(apr_pool_t *pool, conn_rec *c,
                                int default_capacity, 
                                apr_size_t req_buffer_size)
{
    h2_ngn_shed *shed;
    
    shed = apr_pcalloc(pool, sizeof(*shed));
    shed->c = c;
    shed->pool = pool;
    shed->default_capacity = default_capacity;
    shed->req_buffer_size = req_buffer_size;
    shed->ngns = apr_hash_make(pool);
    
    return shed;
}