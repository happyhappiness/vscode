void SHA1DCSetUseUBC(SHA1_CTX* ctx, int ubc_check)
{
	if (ubc_check)
		ctx->ubc_check = 1;
	else
		ctx->ubc_check = 0;
}