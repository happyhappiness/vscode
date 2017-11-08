void h2_stream_set_iter(h2_stream_set *sp,
                        h2_stream_set_iter_fn *iter, void *ctx)
{
    iter_ctx ictx;
    ictx.iter = iter;
    ictx.ctx = ctx;
    apr_hash_do(hash_iter, &ictx, sp->hash);
}