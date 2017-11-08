static int check_ratio(request_rec *r, deflate_ctx *ctx,
                       const deflate_dirconf_t *dc)
{
    if (ctx->stream.total_in) {
        int ratio = ctx->stream.total_out / ctx->stream.total_in;
        if (ratio < dc->ratio_limit) {
            ctx->ratio_hits = 0;
        }
        else if (++ctx->ratio_hits > dc->ratio_burst) {
            return 0;
        }
    }
    return 1;
}