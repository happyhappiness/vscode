static void sha1_process(SHA1_CTX* ctx, const uint32_t block[16])
{
	unsigned i, j;
	uint32_t ubc_dv_mask[DVMASKSIZE] = { 0xFFFFFFFF };
	uint32_t ihvtmp[5];

	ctx->ihv1[0] = ctx->ihv[0];
	ctx->ihv1[1] = ctx->ihv[1];
	ctx->ihv1[2] = ctx->ihv[2];
	ctx->ihv1[3] = ctx->ihv[3];
	ctx->ihv1[4] = ctx->ihv[4];

	sha1_compression_states(ctx->ihv, block, ctx->m1, ctx->states);

	if (ctx->detect_coll)
	{
		if (ctx->ubc_check)
		{
			ubc_check(ctx->m1, ubc_dv_mask);
		}

		if (ubc_dv_mask[0] != 0)
		{
			for (i = 0; sha1_dvs[i].dvType != 0; ++i)
			{
				if (ubc_dv_mask[0] & ((uint32_t)(1) << sha1_dvs[i].maskb))
				{
					for (j = 0; j < 80; ++j)
						ctx->m2[j] = ctx->m1[j] ^ sha1_dvs[i].dm[j];

					sha1_recompression_step(sha1_dvs[i].testt, ctx->ihv2, ihvtmp, ctx->m2, ctx->states[sha1_dvs[i].testt]);

					/* to verify SHA-1 collision detection code with collisions for reduced-step SHA-1 */
					if ((0 == ((ihvtmp[0] ^ ctx->ihv[0]) | (ihvtmp[1] ^ ctx->ihv[1]) | (ihvtmp[2] ^ ctx->ihv[2]) | (ihvtmp[3] ^ ctx->ihv[3]) | (ihvtmp[4] ^ ctx->ihv[4])))
						|| (ctx->reduced_round_coll && 0==((ctx->ihv1[0] ^ ctx->ihv2[0]) | (ctx->ihv1[1] ^ ctx->ihv2[1]) | (ctx->ihv1[2] ^ ctx->ihv2[2]) | (ctx->ihv1[3] ^ ctx->ihv2[3]) | (ctx->ihv1[4] ^ ctx->ihv2[4]))))
					{
						ctx->found_collision = 1;

						if (ctx->safe_hash)
						{
							sha1_compression_W(ctx->ihv, ctx->m1);
							sha1_compression_W(ctx->ihv, ctx->m1);
						}

						break;
					}
				}
			}
		}
	}
}