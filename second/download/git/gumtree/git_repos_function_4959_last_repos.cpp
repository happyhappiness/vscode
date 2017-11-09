void SHA1DCSetUseDetectColl(SHA1_CTX* ctx, int detect_coll)
{
	if (detect_coll)
		ctx->detect_coll = 1;
	else
		ctx->detect_coll = 0;
}