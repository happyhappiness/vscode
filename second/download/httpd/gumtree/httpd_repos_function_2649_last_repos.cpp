static int read_link(link_ctx *ctx)
{
    ctx->link_start = ctx->link_end = 0;
    if (skip_ws(ctx) && read_chr(ctx, '<')) {
        int end;
        if (find_chr(ctx, '>', &end)) {
            ctx->link_start = ctx->i;
            ctx->link_end = end;
            ctx->i = end + 1;
            return 1;
        }
    }
    return 0;
}