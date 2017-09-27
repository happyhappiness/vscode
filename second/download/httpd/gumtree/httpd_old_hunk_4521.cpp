
#include "h2_filter.h"

#define UNSET       -1
#define H2MIN(x,y) ((x) < (y) ? (x) : (y))

static apr_status_t consume_brigade(h2_filter_cin *cin, 
                                    apr_bucket_brigade *bb, 
                                    apr_read_type_e block)
{
    apr_status_t status = APR_SUCCESS;
    apr_size_t readlen = 0;
    
    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
        
        apr_bucket* bucket = APR_BRIGADE_FIRST(bb);
        if (APR_BUCKET_IS_METADATA(bucket)) {
            /* we do nothing regarding any meta here */
        }
        else {
            const char *bucket_data = NULL;
            apr_size_t bucket_length = 0;
            status = apr_bucket_read(bucket, &bucket_data,
                                     &bucket_length, block);
            
            if (status == APR_SUCCESS && bucket_length > 0) {
                apr_size_t consumed = 0;

                status = cin->cb(cin->cb_ctx, bucket_data, bucket_length, &consumed);
                if (status == APR_SUCCESS && bucket_length > consumed) {
                    /* We have data left in the bucket. Split it. */
                    status = apr_bucket_split(bucket, consumed);
                }
                readlen += consumed;
                cin->start_read = apr_time_now();
            }
        }
        apr_bucket_delete(bucket);
    }
    
    if (readlen == 0 && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
        return APR_EAGAIN;
    }
    return status;
}

h2_filter_cin *h2_filter_cin_create(apr_pool_t *p, h2_filter_cin_cb *cb, void *ctx)
{
    h2_filter_cin *cin;
    
    cin = apr_pcalloc(p, sizeof(*cin));
    cin->pool      = p;
    cin->cb        = cb;
    cin->cb_ctx    = ctx;
    cin->start_read = UNSET;
    return cin;
}

void h2_filter_cin_timeout_set(h2_filter_cin *cin, apr_interval_time_t timeout)
{
    cin->timeout = timeout;
