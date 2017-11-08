apr_status_t h2_transfer_brigade(apr_bucket_brigade *to,
                                 apr_bucket_brigade *from, 
                                 apr_pool_t *p)
{
    apr_bucket *e;
    apr_status_t rv;

    while (!APR_BRIGADE_EMPTY(from)) {
        e = APR_BRIGADE_FIRST(from);
        
        rv = apr_bucket_setaside(e, p);
        
        /* If the bucket type does not implement setaside, then
         * (hopefully) morph it into a bucket type which does, and set
         * *that* aside... */
        if (rv == APR_ENOTIMPL) {
            const char *s;
            apr_size_t n;
            
            rv = apr_bucket_read(e, &s, &n, APR_BLOCK_READ);
            if (rv == APR_SUCCESS) {
                rv = apr_bucket_setaside(e, p);
            }
        }
        
        if (rv != APR_SUCCESS) {
            /* Return an error but still save the brigade if
             * ->setaside() is really not implemented. */
            if (rv != APR_ENOTIMPL) {
                return rv;
            }
        }
        
        APR_BUCKET_REMOVE(e);
        APR_BRIGADE_INSERT_TAIL(to, e);
    }
    return APR_SUCCESS;
}