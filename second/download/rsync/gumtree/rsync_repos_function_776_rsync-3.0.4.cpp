void md5_result(md_context *ctx, uchar digest[MD5_DIGEST_LEN])
{
	uint32 last, padn;
	uint32 high, low;
	uchar msglen[8];

	high = (ctx->totalN >> 29)
	     | (ctx->totalN2 <<  3);
	low  = (ctx->totalN <<  3);

	SIVAL(msglen, 0, low);
	SIVAL(msglen, 4, high);

	last = ctx->totalN & 0x3F;
	padn = last < 56 ? 56 - last : 120 - last;

	md5_update(ctx, md5_padding, padn);
	md5_update(ctx, msglen, 8);

	SIVAL(digest, 0, ctx->A);
	SIVAL(digest, 4, ctx->B);
	SIVAL(digest, 8, ctx->C);
	SIVAL(digest, 12, ctx->D);
}