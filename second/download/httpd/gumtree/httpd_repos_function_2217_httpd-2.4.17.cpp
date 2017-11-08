static h2_ngheader *make_ngheader(apr_pool_t *pool, const char *status,
                                  apr_table_t *header)
{
    size_t n;
    h2_ngheader *h;
    nvctx_t ctx;
    
    ctx.nv       = NULL;
    ctx.nvlen    = 1;
    ctx.nvstrlen = strlen(status) + 1;
    ctx.offset   = 0;
    ctx.strbuf   = NULL;
    ctx.pool     = pool;
    
    apr_table_do(count_header, &ctx, header, NULL);
    
    n =  (sizeof(h2_ngheader)
                 + (ctx.nvlen * sizeof(nghttp2_nv)) + ctx.nvstrlen); 
    h = apr_pcalloc(pool, n);
    if (h) {
        ctx.nv = (nghttp2_nv*)(h + 1);
        ctx.strbuf = (char*)&ctx.nv[ctx.nvlen];
        
        NV_ADD_LIT_CS(&ctx, ":status", status);
        apr_table_do(add_header, &ctx, header, NULL);
        
        h->nv = ctx.nv;
        h->nvlen = ctx.nvlen;
    }
    return h;
}