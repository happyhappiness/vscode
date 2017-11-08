void md5_begin(md_context *ctx)
{
	ctx->A = 0x67452301;
	ctx->B = 0xEFCDAB89;
	ctx->C = 0x98BADCFE;
	ctx->D = 0x10325476;

	ctx->totalN = ctx->totalN2 = 0;
}