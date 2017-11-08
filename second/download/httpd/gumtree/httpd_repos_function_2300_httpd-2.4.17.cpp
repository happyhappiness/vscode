void h2_io_set_iter(h2_io_set *sp,
                        h2_io_set_iter_fn *iter, void *ctx)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_io *s = h2_io_IDX(sp->list, i);
        if (!iter(ctx, s)) {
            break;
        }
    }
}