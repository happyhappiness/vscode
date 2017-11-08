size_t h2_ihash_ishift(h2_ihash_t *ih, int *buffer, size_t max)
{
    icollect_ctx ctx;
    size_t i;
    
    ctx.ih = ih;
    ctx.buffer = buffer;
    ctx.max = max;
    ctx.len = 0;
    h2_ihash_iter(ih, icollect_iter, &ctx);
    for (i = 0; i < ctx.len; ++i) {
        h2_ihash_remove(ih, buffer[i]);
    }
    return ctx.len;
}