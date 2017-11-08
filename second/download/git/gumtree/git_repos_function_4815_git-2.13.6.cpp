void SHA1DCSetSafeHash(SHA1_CTX* ctx, int safehash)
{
	if (safehash)
		ctx->safe_hash = 1;
	else
		ctx->safe_hash = 0;
}