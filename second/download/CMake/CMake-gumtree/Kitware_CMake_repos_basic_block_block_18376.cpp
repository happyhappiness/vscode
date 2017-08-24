{
		size_t left = block_size - index;
		memcpy((char*)ctx->message + index, msg, (size < left ? size : left));
		if (size < left) return;

		/* process partial block */
		rhash_sha3_process_block(ctx->hash, ctx->message, block_size);
		msg  += left;
		size -= left;
	}