static void window_release(struct window *ctx)
{
	strbuf_release(&ctx->out);
	strbuf_release(&ctx->instructions);
	strbuf_release(&ctx->data);
}