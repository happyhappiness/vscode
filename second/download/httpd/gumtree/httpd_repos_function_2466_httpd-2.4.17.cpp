h2_stream *h2_stream_set_find(h2_stream_set *sp,
                              h2_stream_set_match_fn *match, void *ctx)
{
    h2_stream *s = NULL;
    int i;
    for (i = 0; !s && i < sp->list->nelts; ++i) {
        s = match(ctx, H2_STREAM_IDX(sp->list, i));
    }
    return s;
}