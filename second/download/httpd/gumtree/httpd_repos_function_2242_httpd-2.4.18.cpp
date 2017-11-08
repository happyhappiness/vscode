apr_status_t h2_util_bb_readx(apr_bucket_brigade *bb, 
                              h2_util_pass_cb *cb, void *ctx, 
                              apr_off_t *plen, int *peos)
{
    apr_status_t status = APR_SUCCESS;
    int consume = (cb != NULL);
    apr_off_t written = 0;
    apr_off_t avail = *plen;
    apr_bucket *next, *b;
    
    /* Pass data in our brigade through the callback until the length
     * is satisfied or we encounter an EOS.
     */
    *peos = 0;
    for (b = APR_BRIGADE_FIRST(bb);
         (status == APR_SUCCESS) && (b != APR_BRIGADE_SENTINEL(bb));
         b = next) {
        
        if (APR_BUCKET_IS_METADATA(b)) {
            if (APR_BUCKET_IS_EOS(b)) {
                *peos = 1;
            }
            else {
                /* ignore */
            }
        }
        else if (avail <= 0) {
            break;
        } 
        else {
            const char *data = NULL;
            apr_size_t data_len;
            
            if (b->length == ((apr_size_t)-1)) {
                /* read to determine length */
                status = apr_bucket_read(b, &data, &data_len, APR_NONBLOCK_READ);
            }
            else {
                data_len = b->length;
            }
            
            if (data_len > avail) {
                apr_bucket_split(b, avail);
                data_len = avail;
            }
            
            if (consume) {
                if (!data) {
                    status = apr_bucket_read(b, &data, &data_len, 
                                             APR_NONBLOCK_READ);
                }
                if (status == APR_SUCCESS) {
                    status = cb(ctx, data, data_len);
                }
            }
            else {
                data_len = b->length;
            }
            avail -= data_len;
            written += data_len;
        }
        
        next = APR_BUCKET_NEXT(b);
        if (consume) {
            apr_bucket_delete(b);
        }
    }
    
    *plen = written;
    if (status == APR_SUCCESS && !*peos && !*plen) {
        return APR_EAGAIN;
    }
    return status;
}