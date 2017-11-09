void SHA1DCUpdate(SHA1_CTX* ctx, const char* buf, size_t len)
{
	unsigned left, fill;

	if (len == 0)
		return;

	left = ctx->total & 63;
	fill = 64 - left;

	if (left && len >= fill)
	{
		ctx->total += fill;
		memcpy(ctx->buffer + left, buf, fill);
		sha1_process(ctx, (uint32_t*)(ctx->buffer));
		buf += fill;
		len -= fill;
		left = 0;
	}
	while (len >= 64)
	{
		ctx->total += 64;

#if defined(SHA1DC_ALLOW_UNALIGNED_ACCESS)
		sha1_process(ctx, (uint32_t*)(buf));
#else
		memcpy(ctx->buffer, buf, 64);
		sha1_process(ctx, (uint32_t*)(ctx->buffer));
#endif /* defined(SHA1DC_ALLOW_UNALIGNED_ACCESS) */
		buf += 64;
		len -= 64;
	}
	if (len > 0)
	{
		ctx->total += len;
		memcpy(ctx->buffer + left, buf, len);
	}
}