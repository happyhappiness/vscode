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