static int read_qstring(link_ctx *ctx, const char **ps)
{
    if (skip_ws(ctx) && read_chr(ctx, '\"')) {
        size_t end;
        if (find_chr(ctx, '\"', &end)) {
            *ps = mk_str(ctx, end);
            ctx->i = end + 1;
            return 1;
        }
    }
    return 0;
}