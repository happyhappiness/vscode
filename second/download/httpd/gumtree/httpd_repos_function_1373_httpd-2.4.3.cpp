static void do_expand_cookie(data_item *cookie, rewrite_ctx *ctx)
{
    while (cookie) {
        add_cookie(ctx->r, do_expand(cookie->data, ctx, NULL));
        cookie = cookie->next;
    }

    return;
}