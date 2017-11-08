apr_bucket *brigade_insert_file(apr_bucket_brigade *bb,
                                apr_file_t *f,
                                apr_off_t start,
                                apr_off_t length,
                                apr_pool_t *p)
{
    apr_bucket *e;

    if (sizeof(apr_off_t) == sizeof(apr_size_t) || length < MAX_BUCKET_SIZE) {
        e = apr_bucket_file_create(f, start, (apr_size_t)length, p, 
                                   bb->bucket_alloc);
    }
    else {
        /* Several buckets are needed. */        
        e = apr_bucket_file_create(f, start, MAX_BUCKET_SIZE, p, 
                                   bb->bucket_alloc);

        while (length > MAX_BUCKET_SIZE) {
            apr_bucket *ce;
            apr_bucket_copy(e, &ce);
            APR_BRIGADE_INSERT_TAIL(bb, ce);
            e->start += MAX_BUCKET_SIZE;
            length -= MAX_BUCKET_SIZE;
        }
        e->length = (apr_size_t)length; /* Resize just the last bucket */
    }
    
    APR_BRIGADE_INSERT_TAIL(bb, e);
    return e;
}