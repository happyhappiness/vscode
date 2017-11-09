static apr_status_t ngheader_create(h2_ngheader **ph, apr_pool_t *p, 
                                    int unsafe, size_t key_count, 
                                    const char *keys[], const char *values[],
                                    apr_table_t *headers)
{
    ngh_ctx ctx;
    size_t n, i;
    
    ctx.p = p;
    ctx.unsafe = unsafe;
    
    n = key_count;
    apr_table_do(count_header, &n, headers, NULL);
    
    *ph = ctx.ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    if (!ctx.ngh) {
        return APR_ENOMEM;
    }
    
    ctx.ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    if (!ctx.ngh->nv) {
        return APR_ENOMEM;
    }
    
    ctx.status = APR_SUCCESS;
    for (i = 0; i < key_count; ++i) {
        if (!add_header(&ctx, keys[i], values[i])) {
            return ctx.status;
        }
    }
    
    apr_table_do(add_table_header, &ctx, headers, NULL);

    return ctx.status;
}