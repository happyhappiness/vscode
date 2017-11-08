void h2_stream_set_iter(h2_stream_set *sp,
                        h2_stream_set_iter_fn *iter, void *ctx)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_stream *s = H2_STREAM_IDX(sp->list, i);
        if (!iter(ctx, s)) {
            break;
        }
    }
}