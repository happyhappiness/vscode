void SHA1DCSetDetectReducedRoundCollision(SHA1_CTX* ctx, int reduced_round_coll)
{
	if (reduced_round_coll)
		ctx->reduced_round_coll = 1;
	else
		ctx->reduced_round_coll = 0;
}