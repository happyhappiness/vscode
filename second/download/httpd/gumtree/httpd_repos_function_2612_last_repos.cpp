size_t h2_proxy_ihash_shift(h2_proxy_ihash_t *ih, void **buffer, size_t max)
{
    collect_ctx ctx;
    size_t i;
    
    ctx.ih = ih;
    ctx.buffer = buffer;
    ctx.max = max;
    ctx.len = 0;
    h2_proxy_ihash_iter(ih, collect_iter, &ctx);
    for (i = 0; i < ctx.len; ++i) {
        h2_proxy_ihash_remove_val(ih, buffer[i]);
    }
    return ctx.len;
}