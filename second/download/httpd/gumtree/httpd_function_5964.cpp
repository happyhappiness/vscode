static void make_chunk(h2_task *task, apr_bucket_brigade *bb, 
                       apr_bucket *first, apr_off_t chunk_len, 
                       apr_bucket *tail)
{
    /* Surround the buckets [first, tail[ with new buckets carrying the
     * HTTP/1.1 chunked encoding format. If tail is NULL, the chunk extends
     * to the end of the brigade. */
    char buffer[128];
    apr_bucket *c;
    int len;
    
    len = apr_snprintf(buffer, H2_ALEN(buffer), 
                       "%"APR_UINT64_T_HEX_FMT"\r\n", (apr_uint64_t)chunk_len);
    c = apr_bucket_heap_create(buffer, len, NULL, bb->bucket_alloc);
    APR_BUCKET_INSERT_BEFORE(first, c);
    c = apr_bucket_heap_create("\r\n", 2, NULL, bb->bucket_alloc);
    if (tail) {
        APR_BUCKET_INSERT_BEFORE(tail, c);
    }
    else {
        APR_BRIGADE_INSERT_TAIL(bb, c);
    }
    task->input.chunked_total += chunk_len;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, task->c,
                  "h2_task(%s): added chunk %ld, total %ld", 
                  task->id, (long)chunk_len, (long)task->input.chunked_total);
}