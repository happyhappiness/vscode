apr_status_t h2_util_copy(apr_bucket_brigade *to, apr_bucket_brigade *from, 
                          apr_off_t maxlen, const char *msg)
{
    apr_status_t status = APR_SUCCESS;
    int same_alloc;

    (void)msg;
    AP_DEBUG_ASSERT(to);
    AP_DEBUG_ASSERT(from);
    same_alloc = (to->bucket_alloc == from->bucket_alloc);

    if (!APR_BRIGADE_EMPTY(from)) {
        apr_bucket *b, *end, *cpy;
        
        status = last_not_included(from, maxlen, 0, 0, &end);
        if (status != APR_SUCCESS) {
            return status;
        }

        for (b = APR_BRIGADE_FIRST(from);
             b != APR_BRIGADE_SENTINEL(from) && b != end;
             b = APR_BUCKET_NEXT(b))
        {
            if (same_alloc) {
                status = apr_bucket_copy(b, &cpy);
                if (status != APR_SUCCESS) {
                    break;
                }
                APR_BRIGADE_INSERT_TAIL(to, cpy);
            }
            else {
                if (APR_BUCKET_IS_METADATA(b)) {
                    if (APR_BUCKET_IS_EOS(b)) {
                        APR_BRIGADE_INSERT_TAIL(to, apr_bucket_eos_create(to->bucket_alloc));
                    }
                    else if (APR_BUCKET_IS_FLUSH(b)) {
                        APR_BRIGADE_INSERT_TAIL(to, apr_bucket_flush_create(to->bucket_alloc));
                    }
                    else {
                        /* ignore */
                    }
                }
                else {
                    const char *data;
                    apr_size_t len;
                    status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
                    if (status == APR_SUCCESS && len > 0) {
                        status = apr_brigade_write(to, NULL, NULL, data, len);
#if LOG_BUCKETS                        
                        ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p,
                                      "h2_util_copy: %s, copied bucket %ld-%ld "
                                      "from=%lx(p=%lx) to=%lx(p=%lx)",
                                      msg, (long)b->start, (long)b->length, 
                                      (long)from, (long)from->p, 
                                      (long)to, (long)to->p);
#endif
                    }
                }
            }
        }
    }
    return status;
}