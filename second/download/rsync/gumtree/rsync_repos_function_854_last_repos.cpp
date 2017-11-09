void md5_update(md_context *ctx, const uchar *input, uint32 length)
{
	uint32 left, fill;

	if (!length)
		return;

	left = ctx->totalN & 0x3F;
	fill = CSUM_CHUNK - left;

	ctx->totalN += length;
	ctx->totalN &= 0xFFFFFFFF;

	if (ctx->totalN < length)
		ctx->totalN2++;

	if (left && length >= fill) {
		memcpy(ctx->buffer + left, input, fill);
		md5_process(ctx, ctx->buffer);
		length -= fill;
		input  += fill;
		left = 0;
	}

	while (length >= CSUM_CHUNK) {
		md5_process(ctx, input);
		length -= CSUM_CHUNK;
		input  += CSUM_CHUNK;
	}

	if (length)
		memcpy(ctx->buffer + left, input, length);
}