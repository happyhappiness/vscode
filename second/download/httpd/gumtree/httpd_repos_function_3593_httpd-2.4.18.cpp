static const char *md5_func(ap_expr_eval_ctx_t *ctx, const void *data,
                               const char *arg)
{
	return ap_md5(ctx->p, (const unsigned char *)arg);
}