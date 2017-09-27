        }
    }
    *pend = APR_BRIGADE_SENTINEL(bb);
    return status;
}

apr_status_t h2_brigade_concat_length(apr_bucket_brigade *dest, 
                                      apr_bucket_brigade *src,
                                      apr_off_t length)
{
    apr_bucket *b, *next;
    apr_off_t remain = length;
    apr_status_t status = APR_SUCCESS;
    
    for (b = APR_BRIGADE_FIRST(src); 
         b != APR_BRIGADE_SENTINEL(src);
         b = next) {
        next = APR_BUCKET_NEXT(b);
        
        if (APR_BUCKET_IS_METADATA(b)) {
            /* fall through */
        }
        else {
            if (remain == b->length) {
                /* fall through */
            }
            else if (remain <= 0) {
                return status;
            }
            else {
                if (b->length == ((apr_size_t)-1)) {
                    const char *ign;
                    apr_size_t ilen;
                    status = apr_bucket_read(b, &ign, &ilen, APR_BLOCK_READ);
                    if (status != APR_SUCCESS) {
                        return status;
                    }
                }
            
                if (remain < b->length) {
                    apr_bucket_split(b, remain);
                }
            }
        }
        APR_BUCKET_REMOVE(b);
        APR_BRIGADE_INSERT_TAIL(dest, b);
        remain -= b->length;
    }
    return status;
}

apr_status_t h2_brigade_copy_length(apr_bucket_brigade *dest, 
                                    apr_bucket_brigade *src,
                                    apr_off_t length)
{
    apr_bucket *b, *next;
    apr_off_t remain = length;
    apr_status_t status = APR_SUCCESS;
    
    for (b = APR_BRIGADE_FIRST(src); 
         b != APR_BRIGADE_SENTINEL(src);
         b = next) {
        next = APR_BUCKET_NEXT(b);
        
        if (APR_BUCKET_IS_METADATA(b)) {
            /* fall through */
        }
        else {
            if (remain == b->length) {
                /* fall through */
            }
            else if (remain <= 0) {
                return status;
            }
            else {
                if (b->length == ((apr_size_t)-1)) {
                    const char *ign;
                    apr_size_t ilen;
                    status = apr_bucket_read(b, &ign, &ilen, APR_BLOCK_READ);
                    if (status != APR_SUCCESS) {
                        return status;
                    }
                }
            
                if (remain < b->length) {
                    apr_bucket_split(b, remain);
                }
            }
        }
        status = apr_bucket_copy(b, &b);
        if (status != APR_SUCCESS) {
            return status;
        }
        APR_BRIGADE_INSERT_TAIL(dest, b);
        remain -= b->length;
    }
    return status;
}

int h2_util_has_eos(apr_bucket_brigade *bb, apr_off_t len)
{
