void blk_SHA1_Update(blk_SHA_CTX *ctx, const void *data, unsigned long len)
{
	unsigned int lenW = ctx->size & 63;

	ctx->size += len;

	/* Read the data into W and process blocks as they get full */
	if (lenW) {
		unsigned int left = 64 - lenW;
		if (len < left)
			left = len;
		memcpy(lenW + (char *)ctx->W, data, left);
		lenW = (lenW + left) & 63;
		len -= left;
		data = ((const char *)data + left);
		if (lenW)
			return;
		blk_SHA1_Block(ctx, ctx->W);
	}
	while (len >= 64) {
		blk_SHA1_Block(ctx, data);
		data = ((const char *)data + 64);
		len -= 64;
	}
	if (len)
		memcpy(ctx->W, data, len);
}