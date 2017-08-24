{
		if (index == 15) ctx->message[index] = 0;
		rhash_sha512_process_block(ctx->hash, ctx->message);
		index = 0;
	}