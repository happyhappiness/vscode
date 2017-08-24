{
		/* clear the rest of the data queue */
		memset((char*)ctx->message + ctx->rest, 0, block_size - ctx->rest);
		((char*)ctx->message)[ctx->rest] |= 0x01;
		((char*)ctx->message)[block_size - 1] |= 0x80;

		/* process final block */
		rhash_sha3_process_block(ctx->hash, ctx->message, block_size);
		ctx->rest = SHA3_FINALIZED; /* mark context as finalized */
	}